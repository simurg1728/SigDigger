//
//    DeviceDialogMediator.cpp: Mediate device dialog mediator
//    Copyright (C) 2019 Gonzalo José Carracedo Carballal
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this program.  If not, see
//    <http://www.gnu.org/licenses/>
//

#include "UIMediator.h"
#include "PanoramicDialog.h"

using namespace SigDigger;

bool
UIMediator::getPanSpectrumDevice(Suscan::DeviceProperties &dev) const
{
  return m_ui->panoramicDialog->getSelectedDevice(dev);
}

QString
UIMediator::getPanSpectrumAntenna(void) const
{
  return m_ui->panoramicDialog->getAntenna();
}

bool
UIMediator::getPanSpectrumRange(qint64 &min, qint64 &max) const
{
  if (!m_ui->panoramicDialog->invalidRange()) {
    min = static_cast<qint64>(m_ui->panoramicDialog->getMinFreq());
    max = static_cast<qint64>(m_ui->panoramicDialog->getMaxFreq());
    return true;
  }

  return false;
}

bool
UIMediator::getPanSpectrumZoomRange(qint64 &min, qint64 &max, bool &noHop) const
{
  if (!m_ui->panoramicDialog->invalidRange()) {
    m_ui->panoramicDialog->getZoomRange(min, max, noHop);
    return true;
  }

  return false;
}

unsigned int
UIMediator::getPanSpectrumRttMs(void) const
{
  return m_ui->panoramicDialog->getRttMs();
}

float
UIMediator::getPanSpectrumRelBw(void) const
{
  return m_ui->panoramicDialog->getRelBw();
}

float
UIMediator::getPanSpectrumGain(QString const &name) const
{
  return m_ui->panoramicDialog->getGain(name);
}

SUFREQ
UIMediator::getPanSpectrumLnbOffset(void) const
{
  return m_ui->panoramicDialog->getLnbOffset();
}

float
UIMediator::getPanSpectrumPreferredSampleRate(void) const
{
  return m_ui->panoramicDialog->getPreferredSampleRate();
}

QString
UIMediator::getPanSpectrumStrategy(void) const
{
  return m_ui->panoramicDialog->getStrategy();
}

QString
UIMediator::getPanSpectrumPartition(void) const
{
  return m_ui->panoramicDialog->getPartitioning();
}

void
UIMediator::setMinPanSpectrumBw(quint64 bw)
{
  m_ui->panoramicDialog->setMinBwForZoom(bw);
}

void
UIMediator::feedPanSpectrum(
    quint64 minFreq,
    quint64 maxFreq,
    float *data,
    size_t size)
{
  m_ui->panoramicDialog->feed(minFreq, maxFreq, data, size);
}

void
UIMediator::setPanSpectrumRunning(bool running)
{
  m_ui->panoramicDialog->setRunning(running);
}

void
UIMediator::connectPanoramicDialog(void)
{
  connect(
        m_ui->panoramicDialog,
        SIGNAL(start(void)),
        this,
        SLOT(onPanoramicSpectrumStart(void)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(stop(void)),
        this,
        SLOT(onPanoramicSpectrumStop(void)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(detailChanged(qint64, qint64, bool)),
        this,
        SLOT(onPanoramicSpectrumDetailChanged(qint64, qint64, bool)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(frameSkipChanged(void)),
        this,
        SIGNAL(panSpectrumSkipChanged(void)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(relBandwidthChanged(void)),
        this,
        SIGNAL(panSpectrumRelBwChanged(void)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(reset(void)),
        this,
        SIGNAL(panSpectrumReset(void)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(strategyChanged(QString)),
        this,
        SIGNAL(panSpectrumStrategyChanged(QString)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(partitioningChanged(QString)),
        this,
        SIGNAL(panSpectrumPartitioningChanged(QString)));

  connect(
        m_ui->panoramicDialog,
        SIGNAL(gainChanged(QString, float)),
        this,
        SIGNAL(panSpectrumGainChanged(QString, float)));
}

void
UIMediator::onPanoramicSpectrumStart(void)
{
  emit panSpectrumStart();
}

void
UIMediator::onPanoramicSpectrumStop(void)
{
  emit panSpectrumStop();
}

void
UIMediator::onPanoramicSpectrumDetailChanged(qint64 min, qint64 max, bool noHop)
{
  emit panSpectrumRangeChanged(min, max, noHop);
}
