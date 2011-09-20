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

#ifndef SURVEY_H
#define SURVEY_H

#include <QtCore/QString>
#include <QtCore/QObject>

class QDate;
class QStringList;

class QGraphicsWidget;

class Answer;
class Question;

/**
 * Store the survey data and all the questions.
 * Collect answers.
 * Setup the UI to diplay.
 */
class Survey : public QObject
{
    Q_OBJECT

public:
    /**
     * Minimal constructor.
     * @param parent the parent object
     */
    Survey(QObject* parent = 0);

    /**
     * Full constructor.
     * @param title the title of this survey
     * @param begin the begin date of this survey
     * @param end the end date of this survey
     * @param desc the description of this survey
     * @param author the author of this survey
     * @param email the author's email
     * @param parent the parent object
     * @exception if the end date is before the begin date
     */
    Survey(const QString& title,
           const QDate& begin,
           const QDate& end,
           const QString& desc,
           const QString& author,
           const QString& email,
           QObject* parent = 0)
    throw(QString);

    /**
     * Compares two surveys.
     * Only survey data and questions are compared, not answers (@see AbstractQuestion::operator==)
     * @param other the other survey
     * @return @c true if the two surveys are the same, @c false otherwise
     */
    bool operator==(const Survey& other) const;

    /** Destructor. */
    virtual ~Survey();

    /**
     * Checks if this survey is active or not.
     * Compares the begin/end dates with the current date.
     * @return @c true if this survey is active, @c false otherwise
     */
    bool isActive() const;

    /**
     * Adds a question to this survey.
     * @param number the question's number
     * @param question the question to add
     * @exception if the question's number already exists
     */
    void addQuestion(int number, Question* question) throw(QString);

    /**
     * Returns a string representing this survey.
     * @return the string output
     */
    QString toString() const;

    /**
     * Returns all the selected answers.
     * @param delimiterAnswers the delimiter between each answers
     * @param delimiterQuestions the delimiter between each questions
     * @return the string output
     * @exception if a question is not answerred correctly
     */
    QString getAnswers(const QString& delimiterAnswers = ",", const QString& delimiterQuestions = "-") const throw(QString);

    /**
     * Setup the UI.
     * @param parent the parent's container
     */
    void setupUi(QGraphicsWidget* parent) const;

private:
    class Private;
    Private* const d_ptr;
};

#endif
