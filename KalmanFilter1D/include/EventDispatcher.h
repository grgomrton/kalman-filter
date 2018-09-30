#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

// TODO unused
class EventDispatcher {
public:
    void notify(double distanceInMetres) {

        std::vector<std::weak_ptr<std::function<void(double)>>> brokenListeners;

        for (auto& listener : listeners) {
            if (auto callable = listener.lock()) {
                try {
                    (*callable)(distanceInMetres);
                }
                catch (std::exception& e) {
                    brokenListeners.push_back(listener); // todo log
                }
                catch (...) {
                    brokenListeners.push_back(listener); // todo log
                }
            } else {
                brokenListeners.push_back(listener); // todo log
            }
        }

        auto isBroken = [&](std::weak_ptr<std::function<void(double)>>& listener) {
            for (auto& brokenListener : brokenListeners) {
                if (pointsToSameObject(listener, brokenListener)) {
                    return true;
                }
            }
            return false;
        };
        listeners.erase(std::remove_if(begin(listeners), end(listeners), isBroken), end(listeners));
    }

    void addMoveCommandListener(const std::shared_ptr<std::function<void(double)>>& listener) {
        listeners.push_back(listener); // todo disable multiple subscription
    }

private:
    std::vector<std::weak_ptr<std::function<void(double)>>> listeners;

    template<typename T>
    static bool pointsToSameObject(const std::weak_ptr<T>& item, const std::weak_ptr<T>& itemToCompareWith) {
        return !(item.owner_before(itemToCompareWith) || itemToCompareWith.owner_before(item));
    }

};


