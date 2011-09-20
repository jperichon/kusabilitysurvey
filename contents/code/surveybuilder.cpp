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

#include "surveybuilder.h"

#include <QtCore/QString>

#include <fstream>
#include <sstream>
#include <istream>
#include <string>

#include "survey.h"
#include "questions/question.h"

namespace spirit = boost::spirit;
namespace classic = boost::spirit::classic;

SurveyGrammar<pos_iterator_type> SurveyBuilder::grammar;

bool SurveyBuilder::buildSurvey(const QString& input, Survey*& output)
{
    std::stringstream in(input.toStdString().data());
    return buildSurvey(in, output);
}

bool SurveyBuilder::buildSurvey(std::istream& input, Survey*& output)
{
    base_iterator_type in_begin(input);

    // convert input iterator to forward iterator, usable by spirit parser
    forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
    forward_iterator_type fwd_end;

    // wrap forward iterator with position iterator, to record the position
    pos_iterator_type position_begin(fwd_begin, fwd_end);
    pos_iterator_type position_end;

    bool ret;
    try {
        ret = spirit::qi::phrase_parse(position_begin, position_end, grammar, spirit::ascii::blank, output);
    } catch(const qi::expectation_failure<pos_iterator_type>& e) {
        const classic::file_position_base<std::string>& pos = e.first.get_position();
        std::stringstream msg;
        msg << "parse error at line " << pos.line << " column " << pos.column << std::endl;
        msg << "'" << e.first.get_currentline() << "'" << std::endl;
        throw std::runtime_error(msg.str());
    }
    return ret && position_begin == position_end;
}

bool SurveyBuilder::buildQuestion(std::istream& input, Question*& output)
{
    base_iterator_type in_begin(input);

    // convert input iterator to forward iterator, usable by spirit parser
    forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
    forward_iterator_type fwd_end;

    // wrap forward iterator with position iterator, to record the position
    pos_iterator_type position_begin(fwd_begin, fwd_end);
    pos_iterator_type position_end;

    bool ret = spirit::qi::phrase_parse(position_begin, position_end, grammar.question, spirit::ascii::blank, output);
    return ret && position_begin == position_end;
}

bool SurveyBuilder::buildQuestion(const QString& input, Question*& output)
{
    std::stringstream in(input.toStdString().data());
    return buildQuestion(in, output);
}
