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

#include "radiobuttonquestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <Plasma/RadioButton>

#include <boost/optional.hpp>

#include "simpleclosedquestion_p.h"

class RadioButtonQuestion::Private
{
public:
    QList<Plasma::RadioButton*> m_answers;
};

RadioButtonQuestion::RadioButtonQuestion()
    : d_ptr(new Private)
{
}

RadioButtonQuestion::RadioButtonQuestion(const QString& val,
        const boost::optional<QString>& desc,
        const QStringList& options,
        const boost::optional<bool>& required)
    : SimpleClosedQuestion(val, desc, options, 1, 1, required),
      d_ptr(new Private)
{
}

void RadioButtonQuestion::setupUi(QGraphicsWidget* parent) const
{
    foreach(const QString & option, SimpleClosedQuestion::d_ptr->m_options) {
        Plasma::RadioButton* rb = new Plasma::RadioButton(parent);
        rb->setText(option);
        d_ptr->m_answers.push_back(rb);
    }
}

QStringList RadioButtonQuestion::getAnswers() const throw(QString)
{
    QStringList answers;
    foreach(const Plasma::RadioButton * rb, d_ptr->m_answers) {
        if(rb->isChecked()) {
            answers << rb->text();
        }
    }
    checkNumberAnswers(answers);
    return answers;
}
