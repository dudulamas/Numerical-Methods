#ifndef RESULT_H
#define RESULT_H

struct resultBissecaoFakePoint {
    int round;
    double i1;
    double i2;
    double f1;
    double f2;
    double midpoint;
    double fmidpoint;
    double absolutValueOfInterval;
    bool hasNext;
};

struct resultNewtonRaphson {
  int round;
  double x;
  double fx;
  double xprox;
  double fxprox;
  double xmenusxprox;
  bool hasNext;
};

#endif // RESULT_H

