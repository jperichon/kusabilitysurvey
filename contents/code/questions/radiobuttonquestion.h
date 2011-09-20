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

#ifndef RADIOBUTTONQUESTION_H
#define RADIOBUTTONQUESTION_H

#include "simpleclosedquestion.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

/** Describe a radio button*/
class RadioButtonQuestion : public SimpleClosedQuestion
{
public:
    /** Empty constructor */
    RadioButtonQuestion();

    /**
     * Full constructor.
     * @param val the value of this question
     * @param desc the description of this question (optional)
     * @param options different options for the question
     * @param required indicates whether user has to answer to this or not (optional)
     */
     RadioButtonQuestion(const QString& val,
                        const boost::optional<QString>& desc,
                        const QStringList& options,
                        const boost::optional<bool>& required);

    /**
     * Generates the UI of this question
     * @param parent the parent object
     */
    virtual void setupUi(QGraphicsWidget*) const;

    /**
     * Returns all user's anwers
     * @return the string output
     */
    virtual QStringList getAnswers() const throw(QString);

private:
    class Private;
    Private* const d_ptr;
};

#endif
