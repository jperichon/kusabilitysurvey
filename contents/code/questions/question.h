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

#ifndef QUESTION_H
#define QUESTION_H

#include <QtCore/QString>

class QStringList;
class QGraphicsWidget;

namespace boost
{
template <typename T> class optional;
}

class Answer;

/**
 * Abstract class Question.
 * Manages the question, its answers, and its UI representation.
 */
class Question
{
public:
    /**
     * Minimal constructor.
     */
    Question();

    /**
     * Full constructor.
     * @param val the value of this question
     * @param desc the description of this question (optional)
     * @param required indicates whether user has to answer to this or not (optional)
     */
    Question(const QString& val,
             const boost::optional<QString>& desc,
             const boost::optional<bool>& required);

    /**
     * Destructor.
     */
    virtual ~Question();

    /**
     * Equality operator.
     * Compare all the characteristics of two questions, except answers.
     * @param other the other question to be compared with
     * @return @c true if the two answers are equal, @c false otherwise
     */
    bool operator==(const Question& other) const;

    /**
     * Generates the UI of this question.
     * @param parent the parent object
     */
    virtual void setupUi(QGraphicsWidget* parent) const;

    /**
     * Returns all user's answers.
     * @return user's answers
     * @exception if the question has not been answerred correctly
     */
    virtual QStringList getAnswers() const throw(QString) = 0;

    /**
     * Returns a string representing this question.
     * @return the string output
     */
    virtual QString toString() const;

private:
    class Private;
    Private* const d_ptr;
};

#endif
