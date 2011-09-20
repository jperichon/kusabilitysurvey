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

#include "buttonquestion.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include <Plasma/PushButton>

#include <boost/optional.hpp>

#include "simpleclosedquestion_p.h"

class ButtonQuestion::Private
{
public:
    QList<Plasma::PushButton*> m_answers;
};

ButtonQuestion::ButtonQuestion()
    : d(new Private)
{
}

ButtonQuestion::ButtonQuestion(const QString& val,
                               const boost::optional<QString>& desc,
                               const QStringList& options,
                               const boost::optional<bool>& required)
    : SimpleClosedQuestion(val, desc, options, 1, 1, required),
      d(new Private)
{
}

void ButtonQuestion::setupUi(QGraphicsWidget* parent) const
{
    foreach(const QString & option, d_ptr->m_options) {
        Plasma::PushButton* pb = new Plasma::PushButton(parent);
        pb->setText(option);
    }
}

QStringList ButtonQuestion::getAnswers() const throw(QString)
{
    QStringList answers;
    foreach(const Plasma::PushButton * pb, d->m_answers) {
        if(pb->isChecked()) {
            answers << pb->text();
        }
    }
    checkNumberAnswers(answers);
    return answers;
}

const char* ButtonQuestion::name = "Button";
