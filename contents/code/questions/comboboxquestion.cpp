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

#include "comboboxquestion.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <Plasma/ComboBox>

#include <boost/optional.hpp>

#include "simpleclosedquestion_p.h"

class ComboBoxQuestion::Private
{
public:
    Plasma::ComboBox* m_combobox;
};

ComboBoxQuestion::ComboBoxQuestion()
    : d_ptr(new Private)
{
}

ComboBoxQuestion::ComboBoxQuestion(const QString& val,
                                   const boost::optional<QString>& desc,
                                   const QStringList& options,
                                   const boost::optional<bool>& required)
    : SimpleClosedQuestion(val, desc, options, 1, 1, required),
      d_ptr(new Private())
{
}

void ComboBoxQuestion::setupUi(QGraphicsWidget* parent) const
{
    d_ptr->m_combobox = new Plasma::ComboBox(parent);
    foreach(const QString & option, SimpleClosedQuestion::d_ptr->m_options) {
        d_ptr->m_combobox->addItem(option);
    }
}

QStringList ComboBoxQuestion::getAnswers() const throw(QString)
{
    return QStringList() << SimpleClosedQuestion::d_ptr->m_options.at(d_ptr->m_combobox->currentIndex());
}

const char* ComboBoxQuestion::name = "Combo";
