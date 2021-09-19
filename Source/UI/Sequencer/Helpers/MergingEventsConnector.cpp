/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Common.h"
#include "MergingEventsConnector.h"

MergingEventsConnector::MergingEventsConnector(SafePointer<Component> sourceComponent, Point<float> startPosition) :
    sourceComponent(sourceComponent),
    startPositionAbs(startPosition),
    endPositionAbs(startPosition) {}

MergingEventsConnector::~MergingEventsConnector() = default;

void MergingEventsConnector::setEndPosition(Point<float> position)
{
    this->endPositionAbs = position;
    this->updateBounds();
    this->repaint();
}

void MergingEventsConnector::setTargetComponent(SafePointer<Component> component) noexcept
{
    this->targetComponent = component;
    this->repaint();
}

Point<float> MergingEventsConnector::getStartPosition() const noexcept
{
    const auto *parent = this->getParentComponent();
    jassert(parent != nullptr);

    return parent->getLocalBounds().toFloat().getRelativePoint(this->startPositionAbs.x, this->startPositionAbs.y);
}

Point<float> MergingEventsConnector::getEndPosition() const noexcept
{
    const auto *parent = this->getParentComponent();
    jassert(parent != nullptr);

    return parent->getLocalBounds().toFloat().getRelativePoint(this->endPositionAbs.x, this->endPositionAbs.y);
}

void MergingEventsConnector::parentSizeChanged()
{
    this->updateBounds();
    this->repaint();
    Component::parentSizeChanged();
}

void MergingEventsConnector::updateBounds()
{
    const Rectangle<int> bounds(this->getStartPosition().toInt(), this->getEndPosition().toInt());
    // DBG("  x: " + String(bounds.getX()) + ", y:" + String(bounds.getY()));
    // DBG("  w: " + String(bounds.getWidth()) + ", h:" + String(bounds.getHeight()));
    this->setBounds(bounds.expanded(10));
}

MergingNotesConnector::MergingNotesConnector(SafePointer<Component> sourceComponent, Point<float> startPosition) :
    MergingEventsConnector(sourceComponent, startPosition) {}

void MergingNotesConnector::paint(Graphics &g)
{
    const auto topLeft = this->getBounds().getTopLeft().toFloat();
    const auto start = this->getStartPosition() - topLeft;
    const auto end = this->getEndPosition() - topLeft;

    // todo pretty up:
    g.setColour(Colours::aliceblue);
    g.drawLine(start.x, start.y, end.x, end.y, 1);

    //#if DEBUG
    //    g.setColour(Colours::blanchedalmond.withAlpha(0.1f));
    //    g.fillAll();
    //#endif
}

MergingClipsConnector::MergingClipsConnector(SafePointer<Component> sourceComponent, Point<float> startPosition) :
    MergingEventsConnector(sourceComponent, startPosition)
{
    if (auto *clipComponent = dynamic_cast<ClipComponent *>(sourceComponent.getComponent()))
    {
        this->startColour = clipComponent->getClip().getTrackColour();
        this->endColour = this->startColour;
    }
}

void MergingClipsConnector::setTargetComponent(SafePointer<Component> component) noexcept
{
    if (auto *clipComponent = dynamic_cast<ClipComponent *>(component.getComponent()))
    {
        this->endColour = clipComponent->getClip().getTrackColour();
    }
    else
    {
        this->endColour = this->startColour;
    }

    MergingEventsConnector::setTargetComponent(component);
}

void MergingClipsConnector::paint(Graphics &g)
{
    const auto topLeft = this->getBounds().getTopLeft().toFloat();
    const auto start = this->getStartPosition() - topLeft;
    const auto end = this->getEndPosition() - topLeft;

    // todo pretty up:
    const auto distanceSqr = end.getDistanceSquaredFrom(start);
    const auto crossSize = jmin(distanceSqr / 100.f, 9.f);

    g.setGradientFill(ColourGradient(this->startColour, start, this->endColour, end, false));
    g.drawArrow(Line<float>(start, end), 1.f, crossSize * 0.8f, crossSize * 2.2f);
    // g.drawLine(start.x, start.y, end.x, end.y, 1);

    g.fillRect(start.x - crossSize, start.y, crossSize * 2.f, 1.f);
    g.fillRect(start.x, start.y - crossSize, 1.f, crossSize * 2.f);

    //#if DEBUG
    //    g.setColour(Colours::blanchedalmond.withAlpha(0.1f));
    //    g.fillAll();
    //#endif
}
