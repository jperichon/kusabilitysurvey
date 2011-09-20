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

#include "surveygrammar.h"

namespace boost
{
namespace spirit
{
namespace traits
{
/* Make boost::spirit able to synthetize QString objects. */
template <> struct is_container<QString> : mpl::true_ {};
template <> struct container_value<QString> : mpl::identity<QChar> {};
template <> struct push_back_container<QString, QChar> {
    static bool call(QString& c, QChar const& val) {
        c.append(val);
        return true;
    }
};

/* Make boost::spirit able to synthetize QList objects. */
template <class T> struct is_container<QList<T> > : mpl::true_ {};
template <class T> struct container_value<QList<T> > : mpl::identity<T> {};
template <class T> struct push_back_container<QList<T>, T> {
    static bool call(QList<T>& c, T const& val) {
        c.push_back(val);
        return true;
    }
};

/* Make boost::spirit able to synthetize QStringList objects. */
template <> struct is_container<QStringList> : mpl::true_ {};
template <> struct container_value<QStringList> : mpl::identity<QString> {};
template <> struct push_back_container<QStringList, QString> {
    static bool call(QStringList& c, QString const& val) {
        c.append(val);
        return true;
    }
};
}
}
}

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

template <typename Iterator>
SurveyGrammar<Iterator>::SurveyGrammar(char delimiter, char optionDelimiter)
    : SurveyGrammar::base_type(survey)
{

    using qi::lit;
    using qi::eol;
    using qi::char_;
    using qi::bool_;
    using qi::int_;
    using phoenix::construct;
    using phoenix::new_;
    using phoenix::bind;
    using namespace qi::labels;

    unquoted_str    %= *lit(' ')
                       >> +(!(*lit(' ') >> (delimiter | eol))
                            >> (char_ - delimiter))
                       >> *lit(' ');

    quoted_str      %= '"' >> +(char_ - '"') >> '"';

    unquoted_opt    %= *lit(' ')
                       >> +(!(*lit(' ') >> optionDelimiter | delimiter)
                            >> (char_ - optionDelimiter - delimiter))
                       >> *lit(' ');

    qstring         %= quoted_str | unquoted_str;

    qdate            = (int_ >> '-' >> int_ >> '-' >> int_)
                       [ _val = construct<QDate>(_1, _2, _3) ];

    qstringlist     %= (quoted_str | unquoted_opt) % optionDelimiter;

    open_q           = (qstring >> delimiter >> -qstring >> delimiter >> OpenQuestion::name
                        >> delimiter >> -bool_ >> delimiter >> -int_ >> delimiter >> delimiter)
                       [ _val = new_<OpenQuestion>(_1, _2, _4, _3) ];

    scale_q          = (qstring >> delimiter >> -qstring >> delimiter >> ScaleQuestion::name
                        >> delimiter >> -bool_ >> delimiter >> qstringlist >> delimiter >> qstring >> delimiter >> qstring)
                       [ _val = new_<ScaleQuestion>(_1, _2, _4, _5, _6, _3) ];

    grid_q           = (qstring >> delimiter >> -qstring >> delimiter >> GridQuestion::name
                        >> delimiter >> -bool_ >> delimiter >> qstringlist >> delimiter >> qstringlist >> delimiter)
                       [ _val = new_<GridQuestion>(_1, _2, _4, _5, _3) ];

    button_q         = (qstring >> delimiter >> -qstring >> delimiter >> ButtonQuestion::name
                        >> delimiter >> qstringlist >> delimiter >> delimiter >> -bool_)
                       [ _val = new_<ButtonQuestion>(_1, _2, _3, _4) ];

    combobox_q       = (qstring >> delimiter >> -qstring >> delimiter >> ComboBoxQuestion::name
                        >> delimiter >> qstringlist >> delimiter >> delimiter >> -bool_)
                       [ _val = new_<ComboBoxQuestion>(_1, _2, _3, _4) ];

    checkbox_q         = (qstring >> delimiter >> -qstring >> delimiter >> CheckBoxQuestion::name
                          >> delimiter >> -bool_ >> delimiter >> qstringlist >> delimiter >> -int_ >> delimiter >> -int_)
                         [ _val = new_<CheckBoxQuestion>(_1, _2, _4, _5, _6, _3) ];

    question         %= open_q | scale_q | grid_q | checkbox_q | combobox_q | button_q;

    survey          = (-lit(surveyHeader) > *eol > qstring > delimiter > qdate > delimiter > qdate
                       > delimiter > qstring > delimiter > qstring
                       > delimiter > qstring)
                      [ _val = new_<Survey>(_1, _2, _3, _4, _5, _6) ]
                      > *eol > -lit(questionHeader) > *eol
                      > (int_ > delimiter > question) [ bind(&Survey::addQuestion, _val, _1, _2) ] % eol
                      > *eol;

}
