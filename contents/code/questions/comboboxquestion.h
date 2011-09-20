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

#ifndef COMBOBOXQUESTION_H
#define COMBOBOXQUESTION_H

#include "simpleclosedquestion.h"

class QStringList;
class QGraphicsWidget;
class QString;

namespace boost
{
template <typename T> class optional;
}

/**
 * ComboBox question: multiple choices question.
 * Options are represented in a combobox.
 * Only one option can be selected.
 */
class ComboBoxQuestion : public SimpleClosedQuestion
{
public:
    /**
     * Minimal constructor
     */
    ComboBoxQuestion();

    /**
     * Full constructor.
     * @param val the question's value
     * @param desc the question's description (optional)
     * @param options the question's options
     * @param required indicates whether user has to answer to this or not (optional)
     */
    ComboBoxQuestion(const QString& val,
                     const boost::optional<QString>& desc,
                     const QStringList& options,
                     const boost::optional<bool>& required);

    /**
     * Generates the UI of this question.
     * @param parent the parent object
     */
    virtual void setupUi(QGraphicsWidget* parent) const;

    virtual QStringList getAnswers() const throw(QString);

    /** Question type's name */
    static const char* name;

private:
    class Private;
    Private* const d_ptr;
};

#endif
