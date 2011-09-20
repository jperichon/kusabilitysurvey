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

#ifndef SURVEYBUILDER_H
#define SURVEYBUILDER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#include "surveygrammar.cpp"

class QString;

class Survey;
class Question;

typedef std::istreambuf_iterator<char> base_iterator_type;
typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
typedef boost::spirit::classic::position_iterator2<forward_iterator_type> pos_iterator_type;

/**
 * Build a Survey or a Question, using the grammar.
 */
class SurveyBuilder
{
private:
    /** The grammar which is instantiated once. */
    static SurveyGrammar<pos_iterator_type> grammar;

    /**
     * Build a Survey from a std::istream.
     * @param input the input stream
     * @param output the Survey parsed
     * @return @c true if it parses successfully, @c false otherwise
     */
    static bool buildSurvey(std::istream& input, Survey*& output);

    /**
     * Build a Question from a std::istream.
     * @param input the input stream
     * @param output the Question parsed
     * @return @c true if it parses successfully, @c false otherwise
     */
    static bool buildQuestion(std::istream& input, Question*& output);

public:
    /**
     * Build a Survey from a string or a file.
     * @param input the input string or file
     * @param output the Survey parsed
     * @return @c true if it parses successfully, @c false otherwise
     */
    static bool buildSurvey(const QString& input, Survey*& output);

    /**
     * Build a Question from a string.
     * @param input the input string
     * @param output the Question parsed
     * @return @c true if it parses successfully, @c false otherwise
     */
    static bool buildQuestion(const QString& input, Question*& output);
};

#endif
