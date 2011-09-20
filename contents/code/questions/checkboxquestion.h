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

#ifndef CHECKBOXQUESTION_H
#define CHECKBOXQUESTION_H

#include "simpleclosedquestion.h"

class QString;
class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

/**
 * CheckBox question: multiples choices question.
 * Each options are represented by a checkbox.
 * Multiples options can be selected.
 */
class CheckBoxQuestion : public SimpleClosedQuestion
{
public:
    /**
     * Minimal constructor.
     */
    CheckBoxQuestion();

    /**
     * Full constructor.
     * @param val the question's value
     * @param desc the question's description (optional)
     * @param options the question's options
     * @param minAnswers the min number of answers
     * @param maxAnswers the max number of answers
     * @param required indicates whether user has to answer to this or not (optional)
     */
    CheckBoxQuestion(const QString& val,
                     const boost::optional<QString>& desc,
                     const QStringList& options,
                     const boost::optional<int>& minAnswers,
                     const boost::optional<int>& maxAnswers,
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
