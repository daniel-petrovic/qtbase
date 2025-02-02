// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qwasmdom.h"

#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>

#include <utility>

QT_BEGIN_NAMESPACE

namespace dom {
void syncCSSClassWith(emscripten::val element, std::string cssClassName, bool flag)
{
    if (flag) {
        element["classList"].call<void>("add", emscripten::val(std::move(cssClassName)));
        return;
    }

    element["classList"].call<void>("remove", emscripten::val(std::move(cssClassName)));
}

QPoint mapPoint(emscripten::val source, emscripten::val target, const QPoint &point)
{
    auto sourceBoundingRect =
            QRectF::fromDOMRect(source.call<emscripten::val>("getBoundingClientRect"));
    auto targetBoundingRect =
            QRectF::fromDOMRect(target.call<emscripten::val>("getBoundingClientRect"));

    auto offset = sourceBoundingRect.topLeft() - targetBoundingRect.topLeft();
    return (point + offset).toPoint();
}
} // namespace dom

QT_END_NAMESPACE
