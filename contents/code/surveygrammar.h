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

#ifndef SURVEYGRAMMAR_H
#define SURVEYGRAMMAR_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "survey.h"
#include "questions/openquestion.h"
#include "questions/gridquestion.h"
#include "questions/scalequestion.h"
#include "questions/buttonquestion.h"
#include "questions/comboboxquestion.h"
#include "questions/checkboxquestion.h"
#include "questions/question.h"

/** Survey header which details expected columns for the survey data. */
static const char* surveyHeader = "Title; Begin; End; Description; Author name; Author email";

/** Question header which details expected columns for the question data. */
static const char* questionHeader = "Number; Text; Description; Type; Acceptable responses; Options";

/**
 * Grammar parsing an input and generating a pointer to Survey.
 * This uses boost::spirit::qi (for parsing) and boost::phoenix (for building complex objects) librairies.
 */
template <typename Iterator>
struct SurveyGrammar : boost::spirit::qi::grammar<Iterator, Survey * (), boost::spirit::ascii::blank_type> {

    /**
     * Grammar constructor.
     * @param delimiter the comma delimiter
     * @param optionDelimiter the option delimiter for multiple choices questions
     */
    SurveyGrammar(char delimiter = ';', char optionDelimiter = '|');

    /** Rule synthetizing a QString from a non-empty and unquoted string. */
    boost::spirit::qi::rule<Iterator, QString()> unquoted_str;

    /** Rule synthetizing a QString from a non-empty and unquoted option. */
    boost::spirit::qi::rule<Iterator, QString()> unquoted_opt;

    /** Rule synthetizing a QString from a non-empty and quoted string. */
    boost::spirit::qi::rule<Iterator, QString()> quoted_str;

    /** Rule synthetizing a QString, which can be an unquoted_str or a quoted_str. */
    boost::spirit::qi::rule<Iterator, QString()> qstring;

    /**
     * Rule synthetizing a QStringList, which contains at least 1 string.
     * Strings must be separated by the optionDelimiter.
     */
    boost::spirit::qi::rule<Iterator, QStringList()> qstringlist;

    /** Rule synthetizing a QDate, which is under the format: YYYY-MM-DD. */
    boost::spirit::qi::rule<Iterator, QDate(), boost::spirit::ascii::blank_type> qdate;

    /** Rule synthetizing an OpenQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> open_q;

    /** Rule synthetizing a ScaleQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> scale_q;

    /** Rule synthetizing a GridQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> grid_q;

    /** Rule synthetizing a ButtonQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> button_q;

    /** Rule synthetizing a ComboBoxQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> combobox_q;

    /** Rule synthetizing a CheckBoxQuestion. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> checkbox_q;

    /** Rule synthetizing a Question, following questions types previously defined. */
    boost::spirit::qi::rule<Iterator, Question * (), boost::spirit::ascii::blank_type> question;

    /** Rule synthetizing a Survey, which contains its own data and also multiples questions. */
    boost::spirit::qi::rule<Iterator, Survey * (), boost::spirit::ascii::blank_type> survey;
};

#endif
