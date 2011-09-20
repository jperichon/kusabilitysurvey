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

#include "gridquestion.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QHashIterator>
#include <QtCore/QStringList>

#include <Plasma/Label>
#include <Plasma/RadioButton>

#include <boost/optional.hpp>

#include "gridquestion_p.h"

GridQuestion::GridQuestion()
    : d_ptr(new GridQuestionPrivate)
{
}

GridQuestion::GridQuestion(const QString& val,
                           const boost::optional<QString>& desc,
                           const QStringList& options,
                           const QStringList& items,
                           const boost::optional<bool>& required)
    : ClosedQuestion(val, desc, required, items.size(), items.size()),
      d_ptr(new GridQuestionPrivate)
{
    d_ptr->m_options = options;
    d_ptr->m_items = items;
}

GridQuestion::~GridQuestion()
{
    delete d_ptr;
}

bool GridQuestion::operator==(const GridQuestion& other) const
{
    bool base_eq = ClosedQuestion::operator==(other);
    if(!base_eq || d_ptr->m_options != other.d_ptr->m_options) {
        return false;
    }
    return true;
}

QStringList GridQuestion::getAnswers() const throw(QString)
{
    QStringList answers;
    QHashIterator<QString, QList<Plasma::RadioButton*> > i(d_ptr->m_answers);
    while(i.hasNext()) {
        i.next();
        foreach(const Plasma::RadioButton * answer, i.value()) {
            if(answer->isChecked()) {
                answers << QString(i.key()).append("=").append(answer->text());
            }
        }
    }
    return answers;
}

void GridQuestion::setupUi(QGraphicsWidget* parent) const
{
    foreach(const QString & i, d_ptr->m_items) {
        QList<Plasma::RadioButton*> answers;
        foreach(const QString & o, d_ptr->m_options) {
            Plasma::RadioButton* rb = new Plasma::RadioButton(parent);
            rb->setText(o);
            answers.push_back(rb);
        }
        d_ptr->m_answers.insert(i, answers);
    }
}

QString GridQuestion::toString() const
{
//    QString str = ClosedQuestion::toString() + "\n";
//    str += "Options: ";
//    foreach (const QSharedPointer<Option>& a, d->m_options) {
//        //str += a->toString() + ",";
//    }
//    str += "\nItems: ";
//    foreach (const QString& s, d->m_answers.keys()) {
//        str += s + ",";
//    }
//    return str;
    return QString();
}

const char* GridQuestion::name = "Grid";
