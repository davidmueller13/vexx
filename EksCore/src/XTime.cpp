#include "XTime"
#include "QDebug"
#ifdef Q_OS_WIN
# include <windows.h>
#else
# include <sys/time.h>
#endif

#define SECOND_IN_NANO_SECONDS 1000000000

XTime::XTime(xint64 secs, xint32 nanosecs) : _secs(secs), _nanosecs(nanosecs)
  {
  }

#ifdef Q_OS_WIN
inline LARGE_INTEGER getFrequency() { LARGE_INTEGER freq; xAssert(QueryPerformanceFrequency(&freq)); return freq; }
LARGE_INTEGER frequency(getFrequency());
#endif

XTime XTime::now()
  {
#ifdef Q_OS_WIN
  LARGE_INTEGER time;
  QueryPerformanceCounter(&time);

  xint64 secs = time.QuadPart / frequency.QuadPart;

  xuint64 elapsedNanoseconds = time.QuadPart - (secs * frequency.QuadPart);
  elapsedNanoseconds = (elapsedNanoseconds * SECOND_IN_NANO_SECONDS) / frequency.QuadPart;
  xAssert(elapsedNanoseconds < SECOND_IN_NANO_SECONDS);

  return XTime(secs, elapsedNanoseconds);
#else
  // find the current time from the system in floating point seconds
  struct timeval newTime;
  gettimeofday(&newTime, 0);
  xAssert(newTime.tv_usec < 1000000);
  return XTime(newTime.tv_sec, 1000 * newTime.tv_usec);
#endif
  }

XTime::XTime() : _secs(0), _nanosecs(0)
  {
  }

XTime::XTime(const XTime &t) : _secs(t._secs), _nanosecs(t._nanosecs)
  {
  }

XTime &XTime::operator+=(const XTime &t)
  {
  _secs += t._secs;
  _nanosecs += t._nanosecs;

  _secs += _nanosecs / SECOND_IN_NANO_SECONDS;
  _nanosecs = _nanosecs % SECOND_IN_NANO_SECONDS;

  return *this;
  }

XTime XTime::operator-(const XTime &t) const
  {
  return XTime(_secs - t._secs, _nanosecs - t._nanosecs);
  }

XTime XTime::operator/(double d) const
  {
  xint64 secs = _secs / (xint64)d;

  xint32 nanosecs = _nanosecs / (xint64)d;
  nanosecs += (_secs * SECOND_IN_NANO_SECONDS) / (xint64)d;
  nanosecs = nanosecs % SECOND_IN_NANO_SECONDS;

  return XTime(secs, nanosecs);
  }

bool XTime::operator<(const XTime &t) const
  {
  if(_secs < t._secs)
    {
    return true;
    }
  return _nanosecs < t._nanosecs;
  }
bool XTime::operator>(const XTime &t) const
  {
  if(_secs > t._secs)
    {
    return true;
    }
  return _nanosecs > t._nanosecs;
  }

XTimeStatistics::XTimeStatistics() : _count(0)
  {
  }

void XTimeStatistics::append(XTime t)
  {
  if(_count == 0)
    {
    _minimum = t;
    _maximum = t;
    }
  else
    {
    if(t < _minimum)
      {
      _minimum = t;
      }
    if(t > _maximum)
      {
      _maximum = t;
      }
    }

  _total += t;
  ++_count;
  }

void XTimeStatistics::append(const XTimeStatistics &o)
  {
  if(count() == 0)
    {
    *this = o;
    return;
    }
  else if(o.count() == 0)
    {
    return;
    }

  _count += o.count();
  _total += o.total();

  if(o.minimum() < minimum())
    {
    _minimum = o.minimum();
    }
  if(o.maximum() > maximum())
    {
    _maximum = o.maximum();
    }
  }

void XTimeStatistics::clear()
  {
  _count = 0;
  }
