#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "IMovingObject.h"

class Robot : public IMovingObject {
public:
    explicit Robot(double moveCommandAccuracyInPercentage);

    void move(double distanceInMetres);

    double getMoveCommandAccuracyInPercentage() override;

    void addMoveCommandListener(const std::shared_ptr<std::function<void(double)>>& listener);

private:
    double moveCommandAccuracyInPercentage;
    std::vector<std::weak_ptr<std::function<void(double)>>> listeners;

    template<typename T>
    static bool pointsToSameObject(const std::weak_ptr<T>& item, const std::weak_ptr<T>& itemToCompareWith);
};
