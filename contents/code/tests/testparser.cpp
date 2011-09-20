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

#include "testparser.h"

#include <QtCore/QString>

#include <boost/optional.hpp>

#include "../survey.h"
#include "../questions/question.h"
#include "../questions/openquestion.h"
#include "../questions/checkboxquestion.h"
#include "../questions/scalequestion.h"

class TestParser::Private
{
public:
    boost::optional<int> optInt;
    boost::optional<QString> optQString;
    boost::optional<bool> optBool;
    QStringList options;
    QStringList strings;

    Private() {
        options << "A" << "B" << "C" << "D";
        strings << "Item1" << "Item2" << "Item3";
    }
};

TestParser::TestParser() : d(new Private)
{
}

TestParser::~TestParser()
{
    delete d;
}

void TestParser::benchmark()
{
    QString input =
        "Title; Begin; End; Description; Author name; Author email"
        "\nMy survey title; 2011-07-02; 2011-08-05; \"This is a test\"; Jonathan Perichon; jonathan.perichon@gmail.com"
        "\n1;Text question;Desc;Text;true;50;;"
        "\n2;Grid question;Desc;Grid;true;A|B|C|D;Item1|Item2|Item3;"
        "\n3;Scale question;Desc;Scale;true;A|B|C|D;Min;Max"
        "\n4;Scale question;;Scale;;A|B|C|D;Min;Max"
        "\n5;Text question;Desc;Text;true;50;;"
        "\n6;Grid question;Desc;Grid;true;A|B|C|D;Item1|Item2|Item3;"
        "\n7;Scale question;Desc;Scale;true;A|B|C|D;Min;Max"
        "\n8;Scale question;;Scale;;A|B|C|D;Min;Max"
        "\n9;Text question;Desc;Text;true;50;;"
        "\n10;Grid question;Desc;Grid;true;A|B|C|D;Item1|Item2|Item3;"
        "\n11;Scale question;Desc;Scale;true;A|B|C|D;Min;Max"
        "\n12;Scale question;;Scale;;A|B|C|D;Min;Max";

    QBENCHMARK {
        Survey* s = new Survey();
        SurveyBuilder::buildSurvey(input, s);
        delete s;
    }
}

void TestParser::testOpenQuestion()
{
    QFETCH(QString, input);
    QFETCH(OpenQuestion*, output);
    QFETCH(bool, isParsing);
    QFETCH(bool, isMatching);
    parseQuestion(input, output, isParsing, isMatching);
}

void TestParser::testOpenQuestion_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<OpenQuestion*>("output");
    QTest::addColumn<bool>("isParsing");
    QTest::addColumn<bool>("isMatching");

    QTest::newRow("min")
            << "Text question;;Text;;;;"
            << new OpenQuestion("Text question", d->optQString, d->optInt, d->optBool)
            << true << true;

    QTest::newRow("+required")
            << "Text question;;Text;true;;;"
            << new OpenQuestion("Text question", d->optQString, d->optInt, true)
            << true << true;

    QTest::newRow("+desc")
            << "Text question;Desc;Text;;;;"
            << new OpenQuestion("Text question", QString("Desc"), d->optInt, d->optBool)
            << true << true;

    QTest::newRow("+desc +required")
            << "Text question;Desc;Text;true;;;"
            << new OpenQuestion("Text question", QString("Desc"), d->optInt, true)
            << true << true;

    QTest::newRow("+max length")
            << "Text question;;Text;;50;;"
            << new OpenQuestion("Text question", d->optQString, 50, d->optBool)
            << true << true;

    QTest::newRow("+required +max length")
            << "Text question;;Text;true;50;;"
            << new OpenQuestion("Text question", d->optQString, 50, true)
            << true << true;

    QTest::newRow("+desc +max length")
            << "Text question;Desc;Text;;50;;"
            << new OpenQuestion("Text question", QString("Desc"), 50, d->optBool)
            << true << true;

    QTest::newRow("+desc +required +max length")
            << "Text question;Desc;Text;true;50;;"
            << new OpenQuestion("Text question", QString("Desc"), 50, true)
            << true << true;
}

void TestParser::testScale()
{
    QFETCH(QString, input);
    QFETCH(ScaleQuestion*, output);
    QFETCH(bool, isParsing);
    QFETCH(bool, isMatching);
    parseQuestion(input, output, isParsing, isMatching);
}

void TestParser::testScale_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<ScaleQuestion*>("output");
    QTest::addColumn<bool>("isParsing");
    QTest::addColumn<bool>("isMatching");

    QTest::newRow("min")
            << "Scale question;;Scale;;A|B|C|D;Min;Max"
            << new ScaleQuestion("Scale question", d->optQString, d->options, "Min", "Max", d->optBool)
            << true
            << true;

    QTest::newRow("+required")
            << "Scale question;;Scale;true;A|B|C|D;Min;Max"
            << new ScaleQuestion("Scale question", d->optQString, d->options, "Min", "Max", true)
            << true
            << true;

    QTest::newRow("+desc")
            << "Scale question;Desc;Scale;;A|B|C|D;Min;Max"
            << new ScaleQuestion("Scale question", QString("Desc"), d->options, "Min", "Max", d->optBool)
            << true
            << true;

    QTest::newRow("+desc +requied")
            << "Scale question;Desc;Scale;true;A|B|C|D;Min;Max"
            << new ScaleQuestion("Scale question", QString("Desc"), d->options, "Min", "Max", true)
            << true
            << true;
}

void TestParser::testGrid()
{
    QFETCH(QString, input);
    QFETCH(GridQuestion*, output);
    QFETCH(bool, isParsing);
    QFETCH(bool, isMatching);
    parseQuestion(input, output, isParsing, isMatching);
}

void TestParser::testGrid_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<GridQuestion*>("output");
    QTest::addColumn<bool>("isParsing");
    QTest::addColumn<bool>("isMatching");

    QTest::newRow("min")
            << "Grid question;;Grid;;A|B|C|D;Item1|Item2|Item3;"
            << new GridQuestion("Grid question", d->optQString, d->options, d->strings, d->optBool)
            << true
            << true;

    QTest::newRow("+desc")
            << "Grid question;Desc;Grid;;A|B|C|D;Item1|Item2|Item3;"
            << new GridQuestion("Grid question", QString("Desc"), d->options, d->strings, d->optBool)
            << true
            << true;

    QTest::newRow("+required")
            << "Grid question;;Grid;true;A|B|C|D;Item1|Item2|Item3;"
            << new GridQuestion("Grid question", d->optQString, d->options, d->strings, true)
            << true
            << true;

    QTest::newRow("+desc +required")
            << "Grid question;Desc;Grid;true;A|B|C|D;Item1|Item2|Item3;"
            << new GridQuestion("Grid question", QString("Desc"), d->options, d->strings, true)
            << true
            << true;
}

void TestParser::testCheckbox()
{
    QFETCH(QString, input);
    QFETCH(CheckBoxQuestion*, output);
    QFETCH(bool, isParsing);
    QFETCH(bool, isMatching);
    parseQuestion(input, output, isParsing, isMatching);
}

void TestParser::testCheckbox_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<CheckBoxQuestion*>("output");
    QTest::addColumn<bool>("isParsing");
    QTest::addColumn<bool>("isMatching");

    QTest::newRow("min")
            << "Checkbox question;;Checkbox;;A|B|C|D;;"
            << new CheckBoxQuestion("Checkbox question", d->optQString, d->options, d->optInt, d->optInt, d->optBool)
            << true
            << true;

    QTest::newRow("+minAnswers")
            << "Checkbox question;Desc;Checkbox;false;A|B|C|D;0;"
            << new CheckBoxQuestion("Checkbox question", QString("Desc"), d->options, 0, d->optInt, false)
            << true
            << true;

    QTest::newRow("+desc +optional +minAnswers +maxAnswers")
            << "Checkbox question;Desc;Checkbox;false;A|B|C|D;0;2"
            << new CheckBoxQuestion("Checkbox question", QString("Desc"), d->options, 0, 2, false)
            << true
            << true;
}

QTEST_MAIN(TestParser)

#include "testparser.moc"
