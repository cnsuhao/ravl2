
PACKAGE=Ravl

HEADERS=KalmanFilter.hh LinearKalmanFilter.hh ExtendedKalmanFilter.hh \
 KalmanTwoWheelDifferentialMotionModel.hh KalmanNullMeasurementModel.hh 

SOURCES=KalmanFilter.cc LinearKalmanFilter.cc ExtendedKalmanFilter.cc \
 KalmanTwoWheelDifferentialMotionModel.cc KalmanNullMeasurementModel.cc 

TESTEXES = test_kalman.cc 

PLIB=RavlKalmanFilter

USESLIBS=RavlCore  RavlPatternRec
