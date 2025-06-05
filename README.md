
# EventCallback System for Embedded C++

Este projeto define um sistema de eventos leve, seguro e orientado a objetos para aplicações em sistemas embarcados. Ele permite que objetos se comuniquem usando ponteiros para métodos com diferentes assinaturas, mantendo o sistema desacoplado.

## 📦 Componentes

### `EventManager`

Classe base que define aliases de tipos para facilitar o uso de callbacks:

```cpp
template <typename T>
using CallbackVoid = void (T::*)();      // Para métodos void()

template <typename T, typename P>
using CallbackArg = void (T::*)(P);       // Para argumentos por valor

template <typename T, typename P>
using CallbackRefArg = void (T::*)(P&);   // Para argumentos por referência

template <typename T, typename P>
using CallbackPtrArg = void (T::*)(P*);   // Para ponteiros como argumento
```

---

### `EventCallbackXXX`

Cada classe abaixo implementa um tipo de callback diferente:

- `EventCallbackVoid`: Sem argumento
- `EventCallbackArg<T>`: Argumento por valor
- `EventCallbackRefArg<T>`: Argumento por referência
- `EventCallbackPtrArg<T>`: Ponteiro como argumento

Todos usam ponteiros para métodos membros de classes derivadas de `EventManager`.

---

## ✅ Exemplo: Callback com argumento por valor (`EventCallbackArg<T>`)

```cpp
class Sender : public EventManager {
public:
    void sendEvent(int n) {
        event.invoke(n);
    }

    template<typename T>
    void setEventCallback(T* object, CallbackArg<T, int> method) {
        event.set(object, method);
    }

private:
    EventCallbackArg<int> event;
};

class Receiver : public EventManager {
public:
    Receiver(Sender& sender) : m_sender(&sender) {}

    void init() {
        m_sender->setEventCallback(this, &Receiver::onEvent);
    }

    void onEvent(int n) {
        m_n = n;
    }

    int n() const { return m_n; }

private:
    Sender* m_sender;
    int m_n = 0;
};
```

---

## 🧪 Outros exemplos

### Callback sem argumento (`EventCallbackVoid`)

```cpp
class Button : public EventManager {
public:
    void press() {
        callback.invoke();
    }

    template<typename T>
    void setCallback(T* obj, CallbackVoid<T> method) {
        callback.set(obj, method);
    }

private:
    EventCallbackVoid callback;
};

class Led : public EventManager {
public:
    void toggle() {
        state = !state;
        qDebug() << "LED state:" << state;
    }

private:
    bool state = false;
};
```

---

### Callback com referência (`EventCallbackRefArg<T>`)

```cpp
class Sensor : public EventManager {
public:
    void read() {
        float value = 25.0;
        callback.invoke(value);
    }

    template<typename T>
    void setCallback(T* obj, CallbackRefArg<T, float> method) {
        callback.set(obj, method);
    }

private:
    EventCallbackRefArg<float> callback;
};

class Display : public EventManager {
public:
    void print(float& temp) {
        temp += 0.5;
        qDebug() << "Temp adjusted:" << temp;
    }
};
```

---

### Callback com ponteiro (`EventCallbackPtrArg<T>`)

```cpp
struct Data {
    int x;
};

class Processor : public EventManager {
public:
    void emitData() {
        Data d{42};
        callback.invoke(&d);
    }

    template<typename T>
    void setCallback(T* obj, CallbackPtrArg<T, Data> method) {
        callback.set(obj, method);
    }

private:
    EventCallbackPtrArg<Data> callback;
};

class Consumer : public EventManager {
public:
    void handle(Data* d) {
        qDebug() << "Received:" << d->x;
    }
};
```

---

## 🧠 Segurança e Design

- Todos os objetos precisam herdar de `EventManager`.
- Casts com `reinterpret_cast` são seguros pois o design controla o tipo base comum (`EventManager`).
- `CallbackXXX::invoke(...)` checa se o ponteiro está válido antes de chamar.

---

## 📄 Licença

Uso livre para fins educacionais e comerciais. Mantenha os créditos se possível.
