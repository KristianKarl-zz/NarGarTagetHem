/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "narGarTagetHemPlasmoid.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QTimer>
#include <KLocale>
#include <QNetworkRequest>
#include <QUrl>

#include <plasma/svg.h>
#include <plasma/theme.h>
#include <qnetworkreply.h>
#include <QXmlStreamReader>
#include <qtextcodec.h>

narGarTagetHemPlasmoid::narGarTagetHemPlasmoid ( QObject *parent, const QVariantList &args )
    : Plasma::Applet ( parent, args ) {
  setBackgroundHints ( DefaultBackground );
  resize ( 400, 150 );
  setAutoFillBackground ( true );

  stockholmsCentral = "1002";
  ronningeStation = "9523";
}


narGarTagetHemPlasmoid::~narGarTagetHemPlasmoid() {
}

void narGarTagetHemPlasmoid::init() {
  manager = new QNetworkAccessManager ( this );
  connect ( manager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( replyFinished ( QNetworkReply* ) ) );

  qDebug() << "  Starting!";
  updateDeparture();

  QTimer* m_timer = new QTimer ( this );
  connect ( m_timer, SIGNAL ( timeout() ), this, SLOT ( updateDeparture() ) );
  m_timer->start ( 60000 );
}


void narGarTagetHemPlasmoid::paintInterface ( QPainter *p, const QStyleOptionGraphicsItem*, const QRect &contentsRect ) {
  p->setRenderHint ( QPainter::SmoothPixmapTransform );
  p->setRenderHint ( QPainter::Antialiasing );

  qDebug() << "  Will re-draw widget";

  QString str;
  QTextStream ts ( &str );

  ts << QString::fromLocal8Bit ( "Tåg från Stockholm, söderut:\n" );
  int delay = getData ( &ts, stockholmsCentral, "1" );

  ts << QString::fromLocal8Bit ( "Tåg från Rönninge, norrut:\n" );
  int foo = getData ( &ts, ronningeStation, "2" );
  if ( foo > delay ) {
    delay = foo;
  }

  qDebug() << "  Delay: " << delay;
  QLinearGradient gradient ( QPointF ( 150,400 ), QPointF ( 0,0 ) );
  if ( delay == 0 ) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0, 0.5, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 0 && delay <= 30) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.1, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 30 && delay <= 60) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.2, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 60 && delay <= 90) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.3, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 90 && delay <= 120) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.4, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 120 && delay <= 150) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.5, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 150 && delay <= 180) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.6, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 180 && delay <= 210) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.7, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 210 && delay <= 240) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.8, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else if ( delay > 240 && delay <= 270) {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0.9, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  } else {
    gradient.setColorAt ( 0, QColor::fromRgbF ( 1, 0, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
  }

  QBrush brush ( gradient );
  p->setBrush ( brush );
  p->drawRect ( rect() );
  p->setPen ( Qt::black );
  p->setFont ( QFont ( "Courier New", 10 ) );
  p->drawText ( contentsRect,
                Qt::AlignLeft,
                ts.readAll() );
}

int narGarTagetHemPlasmoid::getData ( QTextStream* ts, const QString& siteId, const QString& journeyDirection ) {
  int delay = 0;
  for ( int i = 0; i < trains.size(); ++i ) {
    QMap<QString, QString> train = trains.at ( i );

    if ( train.contains ( "LineNumber" ) ) {
      QString lineNumber = train.value ( "LineNumber" );
      if ( lineNumber != "36" ) {
        continue;
      }
    } else {
      continue;
    }

    if ( train.contains ( "SiteId" ) ) {
      QString id = train.value ( "SiteId" );
      if ( id == siteId ) {
        if ( train.contains ( "JourneyDirection" ) ) {
          QString jd = train.value ( "JourneyDirection" );
          if ( jd != journeyDirection ) {
            continue;
          }
        }
      } else {
        continue;
      }
    } else {
      continue;
    }

    QTime expectedDateTime;
    QTime timeTabledDateTime;
    if ( train.contains ( "Destination" ) ) {
      *ts << "  ";
      *ts << train.value ( "Destination" );
      *ts << QString::fromLocal8Bit ( " går om " );
    }
    if ( train.contains ( "DisplayTime" ) ) {
      *ts << train.value ( "DisplayTime" ) + ". ";
    }
    if ( train.contains ( "ExpectedDateTime" ) ) {
      //2011-11-01T17:31:12
      expectedDateTime = QDateTime::fromString ( train.value ( "ExpectedDateTime" ), "yyyy-MM-ddTHH:mm:ss" ).time();
      *ts << expectedDateTime.toString();
      qDebug() << "  ExpectedDateTime: " << expectedDateTime.toString();
    }
    if ( train.contains ( "TimeTabledDateTime" ) ) {
      //2011-11-01T17:31:12
      timeTabledDateTime = QDateTime::fromString ( train.value ( "TimeTabledDateTime" ), "yyyy-MM-ddTHH:mm:ss" ).time();
      qDebug() <<   "  TimeTabledDateTime: " << timeTabledDateTime.toString();
    }

    int diff = timeTabledDateTime.secsTo ( expectedDateTime );
    qDebug() << "  Delay: " << diff;
    if ( diff > delay ) {
      delay = diff;
    }
    *ts << "\n";
  }
  return delay;
}


void narGarTagetHemPlasmoid::updateDeparture() {
  QString baseUrl = "https://api.trafiklab.se/sl/realtid/GetDpsDepartures.XML";
  QString key = "<YOU API KEY HERE>";

  trains.clear();

  manager->get ( QNetworkRequest ( QUrl ( baseUrl + "?key=" + key + "&siteId=" + stockholmsCentral ) ) );
  qDebug() << "  Request sent: " << baseUrl + "?key=" + key + "&siteId=" + stockholmsCentral;

  manager->get ( QNetworkRequest ( QUrl ( baseUrl + "?key=" + key + "&siteId=" + ronningeStation ) ) );
  qDebug() << "  Request sent: " << baseUrl + "?key=" + key + "&siteId=" + ronningeStation;
}

void narGarTagetHemPlasmoid::replyFinished ( QNetworkReply* reply ) {
  if ( reply->error() != QNetworkReply::NoError ) {
    qCritical() << "  Request failed, " << reply->errorString();
    return;
  }

  qDebug() << "  Request received successfully";
  processResult ( reply );
  qDebug() << "  Received " << trains.size() << " departures";
  update();
}

void narGarTagetHemPlasmoid::processResult ( QIODevice* source ) {
  QXmlStreamReader reader ( source );

  while ( !reader.atEnd() ) {
    QXmlStreamReader::TokenType tokenType = reader.readNext();

    if ( tokenType == QXmlStreamReader::StartElement ) {
      if ( reader.name() == QString ( "DpsTrain" ) ) {
        reader.readNext();
        trains.append ( readTrain ( reader ) );
      }
    } else if ( tokenType == QXmlStreamReader::Invalid ) {
      return;
    }
  }
}

QMap<QString, QString>  narGarTagetHemPlasmoid::readTrain ( QXmlStreamReader& xml ) {
  QMap<QString, QString> train;

  if ( xml.tokenType() != QXmlStreamReader::StartElement &&
       xml.name() == "DpsTrain" ) {
    return train;
  }

  xml.readNext();
  while ( ! ( xml.tokenType() == QXmlStreamReader::EndElement &&
              xml.name() == "DpsTrain" ) ) {
    if ( xml.tokenType() == QXmlStreamReader::StartElement ) {
      if ( xml.name() == "SiteId" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "LineNumber" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "Destination" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "JourneyDirection" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "TimeTabledDateTime" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "ExpectedDateTime" ) {
        addElementDataToMap ( xml, train );
      }
      if ( xml.name() == "DisplayTime" ) {
        addElementDataToMap ( xml, train );
      }
    }
    xml.readNext();
  }
  return train;
}

void narGarTagetHemPlasmoid::addElementDataToMap ( QXmlStreamReader& xml,
                                       QMap<QString, QString>& map ) const {
  if ( xml.tokenType() != QXmlStreamReader::StartElement ) {
    return;
  }
  QString elementName = xml.name().toString();
  xml.readNext();
  if ( xml.tokenType() != QXmlStreamReader::Characters ) {
    return;
  }
  map.insert ( elementName, xml.text().toString() );
}

#include "narGarTagetHemPlasmoid.moc"
