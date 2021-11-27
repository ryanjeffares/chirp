/*
  ==============================================================================

    CustomListener.h
    Created: 27 Nov 2021 1:24:52am
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <vector>

namespace chirp
{
    template<typename T>
    class CustomBroadcaster;

    template<typename T>
    class CustomListener
    {
    public:
        virtual void customListenerCallback(CustomBroadcaster<T>* broadcaster, T value) = 0;
    };

    template<typename T>
    class CustomBroadcaster
    {
    public:

        void customBroadcast(T value)
        {
            for (unsigned i = 0; i < m_ActiveListeners.size(); i++)
            {
                if (m_ActiveListeners[i])
                    m_ActiveListeners[i]->customListenerCallback(this, value);
            }
        }

        void addCustomListener(CustomListener<T>* listener)
        {
            if (std::find(m_ActiveListeners.begin(), m_ActiveListeners.end(), listener) == m_ActiveListeners.end())
            {
                m_ActiveListeners.push_back(listener);
            }
        }

        bool removeCustomListener(CustomListener<T>* listener)
        {
            auto it = std::find(m_ActiveListeners.begin(), m_ActiveListeners.end(), listener) != m_ActiveListeners.end();
            if (it != m_ActiveListeners.end())
            {
                m_ActiveListeners.erase(it);
                return true;
            }

            return false;
        }

    private:

        std::vector<CustomListener<T>*> m_ActiveListeners;
    };
}
