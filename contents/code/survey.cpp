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

#include "survey.h"

#include <QtCore/QStringList>
#include <QtCore/QDate>
#include <QtCore/QMap>
#include <QtCore/QMapIterator>

#include <QGraphicsWidget>

#include "questions/question.h"

class Survey::Private
{
public:
    QString m_title;
    QDate m_begin;
    QDate m_end;
    QString m_description;
    QString m_author;
    QString m_email;
    QMap<int, QSharedPointer<Question> > m_questions;
};

Survey::Survey(QObject *parent)
    : QObject(parent), d_ptr(new Private)
{
}

Survey::Survey(const QString& title,
               const QDate& begin,
               const QDate& end,
               const QString& desc,
               const QString& author,
               const QString& email,
               QObject *parent)
throw(QString)
    : QObject(parent), d_ptr(new Private)
{
    if(!begin.isValid() || !end.isValid() || end < begin) {
        throw QString("Survey dates are not valid.");
        delete d_ptr;
    }
    d_ptr->m_title = title;
    d_ptr->m_begin = begin;
    d_ptr->m_end = end;
    d_ptr->m_description = desc;
    d_ptr->m_author = author;
    d_ptr->m_email = email;
}

Survey::~Survey()
{
    delete d_ptr;
}

bool Survey::isActive() const
{
    QDate now = QDate::currentDate();
    return now >= d_ptr->m_begin && now <= d_ptr->m_end;
}

void Survey::addQuestion(int number, Question* question) throw(QString)
{
    if(d_ptr->m_questions.contains(number)) {
        throw QString("Duplicates questions with the number: %1").arg(number);
    }
    d_ptr->m_questions.insert(number, QSharedPointer<Question>(question));
}

bool Survey::operator==(const Survey& other) const
{
    bool eq = d_ptr->m_title == other.d_ptr->m_title &&
              d_ptr->m_begin == other.d_ptr->m_begin &&
              d_ptr->m_end == other.d_ptr->m_end &&
              d_ptr->m_description == other.d_ptr->m_description &&
              d_ptr->m_author == other.d_ptr->m_author &&
              d_ptr->m_email == other.d_ptr->m_email &&
              d_ptr->m_questions == other.d_ptr->m_questions;
    return eq;
}

QString Survey::toString() const
{
    QString str;
    str += "\nSurveyData info:";
    str += d_ptr->m_title;
    str += QString("\n\tTitle: %1").arg(d_ptr->m_title);
    str += QString("\n\tBegin date: %1").arg(d_ptr->m_begin.toString());
    str += QString("\n\tEnd date: %1").arg(d_ptr->m_end.toString());
    str += "\nQuestions:";
    str += QString("%1").arg(d_ptr->m_questions.size());

    QMapIterator<int, QSharedPointer<Question> > i(d_ptr->m_questions);
    while(i.hasNext()) {
        i.next();
        str += QString("\n\tNumber %1").arg(i.key());
        str += i.value()->toString();
    }
    str += "\n";
    return str;
}

QString Survey::getAnswers(const QString& delimiterAnswers, const QString& delimiterQuestions) const throw(QString)
{
    QString str;
    QMapIterator<int, QSharedPointer<Question> > i(d_ptr->m_questions);
    while(i.hasNext()) {
        i.next();
        str += i.key();
        try {
            str += i.value()->getAnswers().join(delimiterAnswers);
        } catch(const QString& ex) {
            throw QString("Invalid answers for question %1: %2").arg(i.key()).arg(ex);
        }
        str += delimiterQuestions;
    }
    return str;
}

void Survey::setupUi(QGraphicsWidget* parent) const
{
    QMapIterator<int, QSharedPointer<Question> > i(d_ptr->m_questions);
    while(i.hasNext()) {
        i.next();
        i.value()->setupUi(parent);
    }
}

#include "survey.moc"
