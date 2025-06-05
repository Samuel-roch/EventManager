/**
 ******************************************************************************
 * @file    EventManager.hpp
 * @author  Samuel Almeida Rocha
 * @brief   Event manager for handling callbacks and events.
 ******************************************************************************
 * @attention
 *
 * All rights reserved.
 *
 * This software is licensed under terms described in the LICENSE file,
 * located at the root of this software component.
 * If no LICENSE file is present, the software is provided AS-IS.
 *
 ******************************************************************************
 */

#pragma once

/* * @brief EventManager class for managing events and callbacks.
 *
 * This class provides a mechanism to register and invoke event callbacks
 * with different argument types (void, value, reference, pointer).
 */
class EventManager
{
  template<typename T>
  using CallbackVoid = void (T::*)();

  template<typename T, typename P>
  using CallbackArg = void (T::*)(P);

  template<typename T, typename P>
  using CallbackRefArg = void (T::*)(P&);

  template<typename T, typename P>
  using CallbackPtrArg = void (T::*)(P*);
};

/*
 * EventCallbackVoid class for handling void callbacks.
 * This class allows setting a callback method that takes no arguments
 * and invoking it when needed.
 */
class EventCallbackVoid
{
public:

  /*
   * @brief Invokes the registered callback method.
   */
  void invoke()
  {
    if (m_object && m_eventReceive)
    {
      (m_object->*m_eventReceive)();
    }
  }

  /*
   * @brief Sets the callback method for the event.
   * @tparam T Type of the object that contains the method.
   * @param object Pointer to the object containing the method.
   * @param method Pointer to the method to be called when the event occurs.
   */
  template<typename T>
  void set(T *object, void (T::*method)())
  {
    m_object = static_cast<EventManager*>(object);
    m_eventReceive = reinterpret_cast<void (EventManager::*)()>(method);
  }

private:
  EventManager *m_object = nullptr;
  void (EventManager::*m_eventReceive)() = nullptr;
};

template<typename P>
class EventCallbackArg
{
public:

  /*
   * @brief Invokes the registered callback method with the given value.
   * @param value The value to be passed to the callback method.
   */
  void invoke(P value)
  {
    if (m_object && m_eventReceive)
    {
      (m_object->*m_eventReceive)(value);
    }
  }

  /*
   * @brief Sets the callback method for the event.
   * @tparam T Type of the object that contains the method.
   * @param object Pointer to the object containing the method.
   * @param method Pointer to the method to be called when the event occurs.
   */
  template<typename T>
  void set(T *object, void (T::*method)(P))
  {
    m_object = static_cast<EventManager*>(object);
    m_eventReceive = reinterpret_cast<void (EventManager::*)(P)>(method);
  }

private:
  EventManager *m_object = nullptr;
  void (EventManager::*m_eventReceive)(P) = nullptr;
};

template<typename P>
class EventCallbackRefArg
{
public:
  /*
   * @brief Invokes the registered callback method with the given reference value.
   * @param value The reference value to be passed to the callback method.
   */
  void invoke(P &value)
  {
    if (m_object && m_eventReceive)
    {
      (m_object->*m_eventReceive)(value);
    }
  }

  /*
   * @brief Sets the callback method for the event.
   * @tparam T Type of the object that contains the method.
   * @param object Pointer to the object containing the method.
   * @param method Pointer to the method to be called when the event occurs.
   */
  template<typename T>
  void set(T *object, void (T::*method)(P&))
  {
    m_object = static_cast<EventManager*>(object);
    m_eventReceive = reinterpret_cast<void (EventManager::*)(P&)>(method);
  }

private:
  EventManager *m_object = nullptr;
  void (EventManager::*m_eventReceive)(P&) = nullptr;
};

template<typename P>
class EventCallbackPtrArg
{
public:

  /*
   * @brief Invokes the registered callback method with the given pointer value.
   * @param value Pointer to the value to be passed to the callback method.
   */
  void invoke(P *value)
  {
    if (m_object && m_eventReceive)
    {
      (m_object->*m_eventReceive)(value);
    }
  }

  /*
   * @brief Sets the callback method for the event.
   * @tparam T Type of the object that contains the method.
   * @param object Pointer to the object containing the method.
   * @param method Pointer to the method to be called when the event occurs.
   */
  template<typename T>
  void set(T *object, void (T::*method)(P*))
  {
    m_object = static_cast<EventManager*>(object);
    m_eventReceive = reinterpret_cast<void (EventManager::*)(P*)>(method);
  }

private:
  EventManager *m_object = nullptr;
  void (EventManager::*m_eventReceive)(P*) = nullptr;
};

