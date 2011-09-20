/*
 * Copyright 2011 Jonathan Perichon <jonathan.perichon@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TESTPARSER_H
#define TESTPARSER_H

#include <QtTest>
#include <QDebug>
#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include "../surveybuilder.h"

class QString;

namespace boost
{
template <typename T> class optional;
}

class Survey;
class Question;
class OpenQuestion;
class CheckBoxQuestion;
class ScaleQuestion;

Q_DECLARE_METATYPE(OpenQuestion*)
Q_DECLARE_METATYPE(GridQuestion*)
Q_DECLARE_METATYPE(ScaleQuestion*)
Q_DECLARE_METATYPE(CheckBoxQuestion*)

class TestParser : public QObject
{
    Q_OBJECT

private:
    class Private;
    Private* const d;

    template <typename T>
    void parseQuestion(const QString& input, T* output, bool isParsing, bool isMatching) {
        Question* question;
        bool r = SurveyBuilder::buildQuestion(input, question);
        QCOMPARE(r, isParsing);
        if(isMatching) {
            T* o = static_cast<T*>(question);
            QCOMPARE(*o, *output);
        }
    }

private Q_SLOTS:
    void benchmark();
    void testOpenQuestion();
    void testOpenQuestion_data();
    void testGrid();
    void testGrid_data();
    void testScale();
    void testScale_data();
    void testCheckbox();
    void testCheckbox_data();

public:
    TestParser();
    ~TestParser();
};

#endif
