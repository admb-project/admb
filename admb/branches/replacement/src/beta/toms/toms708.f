C      ALGORITHM 708, COLLECTED ALGORITHMS FROM ACM.
C      THIS WORK PUBLISHED IN TRANSACTIONS ON MATHEMATICAL SOFTWARE,
C      VOL. 18, NO. 3, SEPTEMBER, 1992, PP. 360-373z.
C     PROGRAM BTST (OUTPUT, TAPE6=OUTPUT)
C-----------------------------------------------------------------------
C
C     SAMPLE PROGRAM USING BRATIO. GIVEN THE NONNEGATIVE VALUES
C     A, B, X, Y WHERE A AND B ARE NOT BOTH 0 AND X + Y = 1. THEN
C
C              CALL BRATIO (A, B, X, Y, W, W1, IERR)
C
C     COMPUTES THE VALUES
C
C                W = I (A,B)  AND W1 = 1 - I (A,B).
C                     X                     X
C
C     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS.
C     IF NO INPUT ERRORS ARE DETECTED THEN IERR IS SET TO 0 AND
C     W AND W1 ARE COMPUTED. FOR MORE DETAILS SEE THE IN-LINE
C     DOCUMENTATION OF BRATIO.
C
C     THE LAST FUNCTION IN THIS PACKAGE, IPMPAR, MUST BE DEFINED
C     FOR THE PARTICULAR COMPUTER BEING USED. FOR DETAILS SEE THE
C     IN-LINE DOCUMENTATION OF IPMPAR.
C
C     NO DATA IS READ. THE OUTPUT FOR THE PROGRAM IS WRITTEN ON
C     UNIT 6. THE FIRST STATMENT OF THIS TEXT MAY BE USED TO
C     BEGIN THE PROGRAM FOR THE CDC 6000-7000 SERIES COMPUTERS.
C-----------------------------------------------------------------------
      WRITE (6,1)
    1 FORMAT(11H1   X     Y,11X,1HW,14X,2HW1/)
    2 FORMAT(2F6.2,2E16.6)
C
      A = 5.3
      B = 10.1
      X = 1.E-2
      DO 10 L = 1,50
         Y = 0.5 + (0.5 - X)
         CALL BRATIO (A, B, X, Y, W, W1, IERR)
         IF (IERR .NE. 0) STOP
         WRITE (6,2) X, Y, W, W1
         X = X + 1.E-2
   10 CONTINUE
      STOP
      END 
      SUBROUTINE BRATIO (A, B, X, Y, W, W1, IERR) 
C-----------------------------------------------------------------------
C
C            EVALUATION OF THE INCOMPLETE BETA FUNCTION IX(A,B)
C
C                     --------------------
C
C     IT IS ASSUMED THAT A AND B ARE NONNEGATIVE, AND THAT X .LE. 1
C     AND Y = 1 - X.  BRATIO ASSIGNS W AND W1 THE VALUES
C
C                      W  = IX(A,B)
C                      W1 = 1 - IX(A,B) 
C
C     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS.
C     IF NO INPUT ERRORS ARE DETECTED THEN IERR IS SET TO 0 AND
C     W AND W1 ARE COMPUTED. OTHERWISE, IF AN ERROR IS DETECTED,
C     THEN W AND W1 ARE ASSIGNED THE VALUE 0 AND IERR IS SET TO
C     ONE OF THE FOLLOWING VALUES ...
C
C        IERR = 1  IF A OR B IS NEGATIVE
C        IERR = 2  IF A = B = 0
C        IERR = 3  IF X .LT. 0 OR X .GT. 1
C        IERR = 4  IF Y .LT. 0 OR Y .GT. 1
C        IERR = 5  IF X + Y .NE. 1
C        IERR = 6  IF X = A = 0
C        IERR = 7  IF Y = B = 0
C
C--------------------
C     WRITTEN BY ALFRED H. MORRIS, JR.
C        NAVAL SURFACE WARFARE CENTER
C        DAHLGREN, VIRGINIA
C     REVISED ... NOV 1991
C-----------------------------------------------------------------------
      REAL LAMBDA
C-----------------------------------------------------------------------
C
C     ****** EPS IS A MACHINE DEPENDENT CONSTANT. EPS IS THE SMALLEST 
C            FLOATING POINT NUMBER FOR WHICH 1.0 + EPS .GT. 1.0
C
                       EPS = SPMPAR(1)
C
C-----------------------------------------------------------------------
      W = 0.0
      W1 = 0.0
      IF (A .LT. 0.0 .OR. B .LT. 0.0) GO TO 300
      IF (A .EQ. 0.0 .AND. B .EQ. 0.0) GO TO 310
      IF (X .LT. 0.0 .OR. X .GT. 1.0) GO TO 320
      IF (Y .LT. 0.0 .OR. Y .GT. 1.0) GO TO 330
      Z = ((X + Y) - 0.5) - 0.5
      IF (ABS(Z) .GT. 3.0*EPS) GO TO 340
C
      IERR = 0
      IF (X .EQ. 0.0) GO TO 200
      IF (Y .EQ. 0.0) GO TO 210
      IF (A .EQ. 0.0) GO TO 211
      IF (B .EQ. 0.0) GO TO 201
C
      EPS = AMAX1(EPS, 1.E-15)
      IF (AMAX1(A,B) .LT. 1.E-3*EPS) GO TO 230
C
      IND = 0
      A0 = A
      B0 = B
      X0 = X
      Y0 = Y
      IF (AMIN1(A0, B0) .GT. 1.0) GO TO 30
C
C             PROCEDURE FOR A0 .LE. 1 OR B0 .LE. 1
C
      IF (X .LE. 0.5) GO TO 10
      IND = 1
      A0 = B
      B0 = A
      X0 = Y
      Y0 = X
C
   10 IF (B0 .LT. AMIN1(EPS,EPS*A0)) GO TO 80
      IF (A0 .LT. AMIN1(EPS,EPS*B0) .AND. B0*X0 .LE. 1.0) GO TO 90
      IF (AMAX1(A0, B0) .GT. 1.0) GO TO 20
      IF (A0 .GE. AMIN1(0.2, B0)) GO TO 100
      IF (X0**A0 .LE. 0.9) GO TO 100
      IF (X0 .GE. 0.3) GO TO 110
      N = 20
      GO TO 130
C
   20 IF (B0 .LE. 1.0) GO TO 100
      IF (X0 .GE. 0.3) GO TO 110
      IF (X0 .GE. 0.1) GO TO 21
      IF ((X0*B0)**A0 .LE. 0.7) GO TO 100
   21 IF (B0 .GT. 15.0) GO TO 131
      N = 20
      GO TO 130
C
C             PROCEDURE FOR A0 .GT. 1 AND B0 .GT. 1
C
   30 IF (A .GT. B) GO TO 31
         LAMBDA = A - (A + B)*X
         GO TO 32
   31 LAMBDA = (A + B)*Y - B
   32 IF (LAMBDA .GE. 0.0) GO TO 40
      IND = 1
      A0 = B
      B0 = A
      X0 = Y
      Y0 = X
      LAMBDA = ABS(LAMBDA)
C
   40 IF (B0 .LT. 40.0 .AND. B0*X0 .LE. 0.7) GO TO 100
      IF (B0 .LT. 40.0) GO TO 140
      IF (A0 .GT. B0) GO TO 50
         IF (A0 .LE. 100.0) GO TO 120
         IF (LAMBDA .GT. 0.03*A0) GO TO 120
         GO TO 180
   50 IF (B0 .LE. 100.0) GO TO 120
      IF (LAMBDA .GT. 0.03*B0) GO TO 120
      GO TO 180
C
C            EVALUATION OF THE APPROPRIATE ALGORITHM
C
   80 W = FPSER(A0, B0, X0, EPS)
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
   90 W1 = APSER(A0, B0, X0, EPS)
      W = 0.5 + (0.5 - W1)
      GO TO 220
C
  100 W = BPSER(A0, B0, X0, EPS)
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
  110 W1 = BPSER(B0, A0, Y0, EPS)
      W = 0.5 + (0.5 - W1)
      GO TO 220
C
  120 W = BFRAC(A0, B0, X0, Y0, LAMBDA, 15.0*EPS) 
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
  130 W1 = BUP(B0, A0, Y0, X0, N, EPS)
      B0 = B0 + N
  131 CALL BGRAT(B0, A0, Y0, X0, W1, 15.0*EPS, IERR1)
      W = 0.5 + (0.5 - W1)
      GO TO 220
C
  140 N = B0
      B0 = B0 - N
      IF (B0 .NE. 0.0) GO TO 141
         N = N - 1
         B0 = 1.0
  141 W = BUP(B0, A0, Y0, X0, N, EPS)
      IF (X0 .GT. 0.7) GO TO 150
      W = W + BPSER(A0, B0, X0, EPS)
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
  150 IF (A0 .GT. 15.0) GO TO 151
         N = 20
         W = W + BUP(A0, B0, X0, Y0, N, EPS)
         A0 = A0 + N
  151 CALL BGRAT(A0, B0, X0, Y0, W, 15.0*EPS, IERR1)
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
  180 W = BASYM(A0, B0, LAMBDA, 100.0*EPS)
      W1 = 0.5 + (0.5 - W)
      GO TO 220
C
C               TERMINATION OF THE PROCEDURE
C
  200 IF (A .EQ. 0.0) GO TO 350
  201 W = 0.0
      W1 = 1.0
      RETURN
C
  210 IF (B .EQ. 0.0) GO TO 360
  211 W = 1.0
      W1 = 0.0
      RETURN
C
  220 IF (IND .EQ. 0) RETURN
      T = W
      W = W1
      W1 = T
      RETURN
C
C           PROCEDURE FOR A AND B .LT. 1.E-3*EPS
C
  230 W = B/(A + B) 
      W1 = A/(A + B)
      RETURN
C
C                       ERROR RETURN
C
  300 IERR = 1
      RETURN
  310 IERR = 2
      RETURN
  320 IERR = 3
      RETURN
  330 IERR = 4
      RETURN
  340 IERR = 5
      RETURN
  350 IERR = 6
      RETURN
  360 IERR = 7
      RETURN
      END 
      REAL FUNCTION FPSER (A, B, X, EPS)
C-----------------------------------------------------------------------
C
C                 EVALUATION OF I (A,B) 
C                                X
C
C          FOR B .LT. MIN(EPS,EPS*A) AND X .LE. 0.5.
C
C-----------------------------------------------------------------------
C
C                  SET  FPSER = X**A
C
      FPSER = 1.0
      IF (A .LE. 1.E-3*EPS) GO TO 10
      FPSER = 0.0
      T = A*ALOG(X) 
      IF (T .LT. EXPARG(1)) RETURN
      FPSER = EXP(T)
C
C                NOTE THAT 1/B(A,B) = B 
C
   10 FPSER = (B/A)*FPSER
      TOL = EPS/A
      AN = A + 1.0
      T = X
      S = T/AN
   20    AN = AN + 1.0
         T = X*T
         C = T/AN
         S = S + C
         IF (ABS(C) .GT. TOL) GO TO 20
C
      FPSER = FPSER*(1.0 + A*S)
      RETURN
      END 
      REAL FUNCTION APSER (A, B, X, EPS)
C-----------------------------------------------------------------------
C     APSER YIELDS THE INCOMPLETE BETA RATIO I(SUB(1-X))(B,A) FOR
C     A .LE. MIN(EPS,EPS*B), B*X .LE. 1, AND X .LE. 0.5. USED WHEN
C     A IS VERY SMALL. USE ONLY IF ABOVE INEQUALITIES ARE SATISFIED.
C-----------------------------------------------------------------------
      REAL J
C--------------------
      DATA G/.577215664901533/
C--------------------
      BX = B*X
      T = X - BX
      IF (B*EPS .GT. 2.E-2) GO TO 10
         C = ALOG(X) + PSI(B) + G + T
         GO TO 20
   10 C = ALOG(BX) + G + T
C
   20 TOL = 5.0*EPS*ABS(C)
      J = 1.0
      S = 0.0
   30    J = J + 1.0
         T = T*(X - BX/J)
         AJ = T/J
         S = S + AJ 
         IF (ABS(AJ) .GT. TOL) GO TO 30 
C
      APSER = -A*(C + S)
      RETURN
      END 
      REAL FUNCTION BPSER(A, B, X, EPS) 
C-----------------------------------------------------------------------
C     POWER SERIES EXPANSION FOR EVALUATING IX(A,B) WHEN B .LE. 1
C     OR B*X .LE. 0.7.  EPS IS THE TOLERANCE USED.
C-----------------------------------------------------------------------
      REAL N
C
      BPSER = 0.0
      IF (X .EQ. 0.0) RETURN
C-----------------------------------------------------------------------
C            COMPUTE THE FACTOR X**A/(A*BETA(A,B))
C-----------------------------------------------------------------------
      A0 = AMIN1(A,B)
      IF (A0 .LT. 1.0) GO TO 10
         Z = A*ALOG(X) - BETALN(A,B)
         BPSER = EXP(Z)/A
         GO TO 70
   10 B0 = AMAX1(A,B)
      IF (B0 .GE. 8.0) GO TO 60
      IF (B0 .GT. 1.0) GO TO 40
C
C            PROCEDURE FOR A0 .LT. 1 AND B0 .LE. 1
C
      BPSER = X**A
      IF (BPSER .EQ. 0.0) RETURN
C
      APB = A + B
      IF (APB .GT. 1.0) GO TO 20
         Z = 1.0 + GAM1(APB)
         GO TO 30
   20 U = DBLE(A) + DBLE(B) - 1.D0
      Z = (1.0 + GAM1(U))/APB 
C
   30 C = (1.0 + GAM1(A))*(1.0 + GAM1(B))/Z
      BPSER = BPSER*C*(B/APB) 
      GO TO 70
C
C         PROCEDURE FOR A0 .LT. 1 AND 1 .LT. B0 .LT. 8
C
   40 U = GAMLN1(A0)
      M = B0 - 1.0
      IF (M .LT. 1) GO TO 50
      C = 1.0
      DO 41 I = 1,M 
         B0 = B0 - 1.0
   41    C = C*(B0/(A0 + B0)) 
      U = ALOG(C) + U
C
   50 Z = A*ALOG(X) - U
      B0 = B0 - 1.0 
      APB = A0 + B0 
      IF (APB .GT. 1.0) GO TO 51
         T = 1.0 + GAM1(APB)
         GO TO 52
   51 U = DBLE(A0) + DBLE(B0) - 1.D0
      T = (1.0 + GAM1(U))/APB 
   52 BPSER = EXP(Z)*(A0/A)*(1.0 + GAM1(B0))/T
      GO TO 70
C
C            PROCEDURE FOR A0 .LT. 1 AND B0 .GE. 8
C
   60 U = GAMLN1(A0) + ALGDIV(A0,B0)
      Z = A*ALOG(X) - U
      BPSER = (A0/A)*EXP(Z)
   70 IF (BPSER .EQ. 0.0 .OR. A .LE. 0.1*EPS) RETURN
C-----------------------------------------------------------------------
C                     COMPUTE THE SERIES
C-----------------------------------------------------------------------
      SUM = 0.0
      N = 0.0
      C = 1.0
      TOL = EPS/A
  100    N = N + 1.0
         C = C*(0.5 + (0.5 - B/N))*X
         W = C/(A + N)
         SUM = SUM + W
         IF (ABS(W) .GT. TOL) GO TO 100 
      BPSER = BPSER*(1.0 + A*SUM)
      RETURN
      END 
      REAL FUNCTION BUP(A, B, X, Y, N, EPS)
C-----------------------------------------------------------------------
C     EVALUATION OF IX(A,B) - IX(A+N,B) WHERE N IS A POSITIVE INTEGER.
C     EPS IS THE TOLERANCE USED.
C-----------------------------------------------------------------------
      REAL L
C
C          OBTAIN THE SCALING FACTOR EXP(-MU) AND 
C             EXP(MU)*(X**A*Y**B/BETA(A,B))/A
C
      APB = A + B
      AP1 = A + 1.0 
      MU = 0
      D = 1.0
      IF (N .EQ. 1 .OR. A .LT. 1.0) GO TO 10
      IF (APB .LT. 1.1*AP1) GO TO 10
         MU = ABS(EXPARG(1))
         K = EXPARG(0)
         IF (K .LT. MU) MU = K
         T = MU
         D = EXP(-T)
C
   10 BUP = BRCMP1(MU,A,B,X,Y)/A
      IF (N .EQ. 1 .OR. BUP .EQ. 0.0) RETURN
      NM1 = N - 1
      W = D
C
C          LET K BE THE INDEX OF THE MAXIMUM TERM 
C
      K = 0
      IF (B .LE. 1.0) GO TO 40
      IF (Y .GT. 1.E-4) GO TO 20
         K = NM1
         GO TO 30
   20 R = (B - 1.0)*X/Y - A
      IF (R .LT. 1.0) GO TO 40
      K = NM1
      T = NM1
      IF (R .LT. T) K = R
C
C          ADD THE INCREASING TERMS OF THE SERIES 
C
   30 DO 31 I = 1,K 
         L = I - 1
         D = ((APB + L)/(AP1 + L))*X*D
         W = W + D
   31 CONTINUE
      IF (K .EQ. NM1) GO TO 50
C
C          ADD THE REMAINING TERMS OF THE SERIES
C
   40 KP1 = K + 1
      DO 41 I = KP1,NM1
         L = I - 1
         D = ((APB + L)/(AP1 + L))*X*D
         W = W + D
         IF (D .LE. EPS*W) GO TO 50
   41 CONTINUE
C
C               TERMINATE THE PROCEDURE 
C
   50 BUP = BUP*W
      RETURN
      END 
      REAL FUNCTION BFRAC(A, B, X, Y, LAMBDA, EPS)
C-----------------------------------------------------------------------
C     CONTINUED FRACTION EXPANSION FOR IX(A,B) WHEN A,B .GT. 1.
C     IT IS ASSUMED THAT  LAMBDA = (A + B)*Y - B. 
C-----------------------------------------------------------------------
      REAL LAMBDA, N
C--------------------
      BFRAC = BRCOMP(A,B,X,Y) 
      IF (BFRAC .EQ. 0.0) RETURN
C
      C = 1.0 + LAMBDA
      C0 = B/A
      C1 = 1.0 + 1.0/A
      YP1 = Y + 1.0 
C
      N = 0.0
      P = 1.0
      S = A + 1.0
      AN = 0.0
      BN = 1.0
      ANP1 = 1.0
      BNP1 = C/C1
      R = C1/C
C
C        CONTINUED FRACTION CALCULATION 
C
   10    N = N + 1.0
         T = N/A
         W = N*(B - N)*X
         E = A/S
         ALPHA = (P*(P + C0)*E*E)*(W*X) 
         E = (1.0 + T)/(C1 + T + T)
         BETA = N + W/S + E*(C + N*YP1) 
         P = 1.0 + T
         S = S + 2.0
C
C        UPDATE AN, BN, ANP1, AND BNP1
C
         T = ALPHA*AN + BETA*ANP1
         AN = ANP1
         ANP1 = T
         T = ALPHA*BN + BETA*BNP1
         BN = BNP1
         BNP1 = T
C
         R0 = R
         R = ANP1/BNP1
         IF (ABS(R - R0) .LE. EPS*R) GO TO 20
C
C        RESCALE AN, BN, ANP1, AND BNP1 
C
         AN = AN/BNP1
         BN = BN/BNP1
         ANP1 = R
         BNP1 = 1.0 
         GO TO 10
C
C                 TERMINATION 
C
   20 BFRAC = BFRAC*R
      RETURN
      END 
      REAL FUNCTION BRCOMP (A, B, X, Y) 
C-----------------------------------------------------------------------
C               EVALUATION OF X**A*Y**B/BETA(A,B) 
C-----------------------------------------------------------------------
      REAL LAMBDA, LNX, LNY
C-----------------
C     CONST = 1/SQRT(2*PI)
C-----------------
      DATA CONST/.398942280401433/
C
      BRCOMP = 0.0
      IF (X .EQ. 0.0 .OR. Y .EQ. 0.0) RETURN
      A0 = AMIN1(A,B)
      IF (A0 .GE. 8.0) GO TO 100
C
      IF (X .GT. 0.375) GO TO 10
         LNX = ALOG(X)
         LNY = ALNREL(-X)
         GO TO 20
   10 IF (Y .GT. 0.375) GO TO 11
         LNX = ALNREL(-Y)
         LNY = ALOG(Y)
         GO TO 20
   11 LNX = ALOG(X) 
      LNY = ALOG(Y) 
C
   20 Z = A*LNX + B*LNY
      IF (A0 .LT. 1.0) GO TO 30
      Z = Z - BETALN(A,B)
      BRCOMP = EXP(Z)
      RETURN
C-----------------------------------------------------------------------
C              PROCEDURE FOR A .LT. 1 OR B .LT. 1 
C-----------------------------------------------------------------------
   30 B0 = AMAX1(A,B)
      IF (B0 .GE. 8.0) GO TO 80
      IF (B0 .GT. 1.0) GO TO 60
C
C                   ALGORITHM FOR B0 .LE. 1
C
      BRCOMP = EXP(Z)
      IF (BRCOMP .EQ. 0.0) RETURN
C
      APB = A + B
      IF (APB .GT. 1.0) GO TO 40
         Z = 1.0 + GAM1(APB)
         GO TO 50
   40 U = DBLE(A) + DBLE(B) - 1.D0
      Z = (1.0 + GAM1(U))/APB 
C
   50 C = (1.0 + GAM1(A))*(1.0 + GAM1(B))/Z
      BRCOMP = BRCOMP*(A0*C)/(1.0 + A0/B0)
      RETURN
C
C                ALGORITHM FOR 1 .LT. B0 .LT. 8
C
   60 U = GAMLN1(A0)
      N = B0 - 1.0
      IF (N .LT. 1) GO TO 70
      C = 1.0
      DO 61 I = 1,N 
         B0 = B0 - 1.0
         C = C*(B0/(A0 + B0)) 
   61 CONTINUE
      U = ALOG(C) + U
C
   70 Z = Z - U
      B0 = B0 - 1.0 
      APB = A0 + B0 
      IF (APB .GT. 1.0) GO TO 71
         T = 1.0 + GAM1(APB)
         GO TO 72
   71 U = DBLE(A0) + DBLE(B0) - 1.D0
      T = (1.0 + GAM1(U))/APB 
   72 BRCOMP = A0*EXP(Z)*(1.0 + GAM1(B0))/T
      RETURN
C
C                   ALGORITHM FOR B0 .GE. 8
C
   80 U = GAMLN1(A0) + ALGDIV(A0,B0)
      BRCOMP = A0*EXP(Z - U)
      RETURN
C-----------------------------------------------------------------------
C              PROCEDURE FOR A .GE. 8 AND B .GE. 8
C-----------------------------------------------------------------------
  100 IF (A .GT. B) GO TO 101 
         H = A/B
         X0 = H/(1.0 + H)
         Y0 = 1.0/(1.0 + H)
         LAMBDA = A - (A + B)*X
         GO TO 110
  101 H = B/A
      X0 = 1.0/(1.0 + H)
      Y0 = H/(1.0 + H)
      LAMBDA = (A + B)*Y - B
C
  110 E = -LAMBDA/A 
      IF (ABS(E) .GT. 0.6) GO TO 111
         U = RLOG1(E)
         GO TO 120
  111 U = E - ALOG(X/X0)
C
  120 E = LAMBDA/B
      IF (ABS(E) .GT. 0.6) GO TO 121
         V = RLOG1(E)
         GO TO 130
  121 V = E - ALOG(Y/Y0)
C
  130 Z = EXP(-(A*U + B*V))
      BRCOMP = CONST*SQRT(B*X0)*Z*EXP(-BCORR(A,B))
      RETURN
      END 
      REAL FUNCTION BRCMP1 (MU, A, B, X, Y)
C-----------------------------------------------------------------------
C          EVALUATION OF  EXP(MU) * (X**A*Y**B/BETA(A,B))
C-----------------------------------------------------------------------
      REAL LAMBDA, LNX, LNY
C-----------------
C     CONST = 1/SQRT(2*PI)
C-----------------
      DATA CONST/.398942280401433/
C
      A0 = AMIN1(A,B)
      IF (A0 .GE. 8.0) GO TO 100
C
      IF (X .GT. 0.375) GO TO 10
         LNX = ALOG(X)
         LNY = ALNREL(-X)
         GO TO 20
   10 IF (Y .GT. 0.375) GO TO 11
         LNX = ALNREL(-Y)
         LNY = ALOG(Y)
         GO TO 20
   11 LNX = ALOG(X) 
      LNY = ALOG(Y) 
C
   20 Z = A*LNX + B*LNY
      IF (A0 .LT. 1.0) GO TO 30
      Z = Z - BETALN(A,B)
      BRCMP1 = ESUM(MU,Z)
      RETURN
C-----------------------------------------------------------------------
C              PROCEDURE FOR A .LT. 1 OR B .LT. 1 
C-----------------------------------------------------------------------
   30 B0 = AMAX1(A,B)
      IF (B0 .GE. 8.0) GO TO 80
      IF (B0 .GT. 1.0) GO TO 60
C
C                   ALGORITHM FOR B0 .LE. 1
C
      BRCMP1 = ESUM(MU,Z)
      IF (BRCMP1 .EQ. 0.0) RETURN
C
      APB = A + B
      IF (APB .GT. 1.0) GO TO 40
         Z = 1.0 + GAM1(APB)
         GO TO 50
   40 U = DBLE(A) + DBLE(B) - 1.D0
      Z = (1.0 + GAM1(U))/APB 
C
   50 C = (1.0 + GAM1(A))*(1.0 + GAM1(B))/Z
      BRCMP1 = BRCMP1*(A0*C)/(1.0 + A0/B0)
      RETURN
C
C                ALGORITHM FOR 1 .LT. B0 .LT. 8
C
   60 U = GAMLN1(A0)
      N = B0 - 1.0
      IF (N .LT. 1) GO TO 70
      C = 1.0
      DO 61 I = 1,N 
         B0 = B0 - 1.0
         C = C*(B0/(A0 + B0)) 
   61 CONTINUE
      U = ALOG(C) + U
C
   70 Z = Z - U
      B0 = B0 - 1.0 
      APB = A0 + B0 
      IF (APB .GT. 1.0) GO TO 71
         T = 1.0 + GAM1(APB)
         GO TO 72
   71 U = DBLE(A0) + DBLE(B0) - 1.D0
      T = (1.0 + GAM1(U))/APB 
   72 BRCMP1 = A0*ESUM(MU,Z)*(1.0 + GAM1(B0))/T
      RETURN
C
C                   ALGORITHM FOR B0 .GE. 8
C
   80 U = GAMLN1(A0) + ALGDIV(A0,B0)
      BRCMP1 = A0*ESUM(MU,Z - U)
      RETURN
C-----------------------------------------------------------------------
C              PROCEDURE FOR A .GE. 8 AND B .GE. 8
C-----------------------------------------------------------------------
  100 IF (A .GT. B) GO TO 101 
         H = A/B
         X0 = H/(1.0 + H)
         Y0 = 1.0/(1.0 + H)
         LAMBDA = A - (A + B)*X
         GO TO 110
  101 H = B/A
      X0 = 1.0/(1.0 + H)
      Y0 = H/(1.0 + H)
      LAMBDA = (A + B)*Y - B
C
  110 E = -LAMBDA/A 
      IF (ABS(E) .GT. 0.6) GO TO 111
         U = RLOG1(E)
         GO TO 120
  111 U = E - ALOG(X/X0)
C
  120 E = LAMBDA/B
      IF (ABS(E) .GT. 0.6) GO TO 121
         V = RLOG1(E)
         GO TO 130
  121 V = E - ALOG(Y/Y0)
C
  130 Z = ESUM(MU,-(A*U + B*V))
      BRCMP1 = CONST*SQRT(B*X0)*Z*EXP(-BCORR(A,B))
      RETURN
      END 
      SUBROUTINE BGRAT(A, B, X, Y, W, EPS, IERR)
C-----------------------------------------------------------------------
C     ASYMPTOTIC EXPANSION FOR IX(A,B) WHEN A IS LARGER THAN B.
C     THE RESULT OF THE EXPANSION IS ADDED TO W. IT IS ASSUMED
C     THAT A .GE. 15 AND B .LE. 1.  EPS IS THE TOLERANCE USED.
C     IERR IS A VARIABLE THAT REPORTS THE STATUS OF THE RESULTS.
C-----------------------------------------------------------------------
      REAL J, L, LNX, NU, N2
      REAL C(30), D(30)
C
      BM1 = (B - 0.5) - 0.5
      NU = A + 0.5*BM1
      IF (Y .GT. 0.375) GO TO 10
         LNX = ALNREL(-Y)
         GO TO 11
   10 LNX = ALOG(X) 
   11 Z = -NU*LNX
      IF (B*Z .EQ. 0.0) GO TO 100
C
C                 COMPUTATION OF THE EXPANSION
C                 SET R = EXP(-Z)*Z**B/GAMMA(B)
C
      R = B*(1.0 + GAM1(B))*EXP(B*ALOG(Z))
      R = R*EXP(A*LNX)*EXP(0.5*BM1*LNX) 
      U = ALGDIV(B,A) + B*ALOG(NU)
      U = R*EXP(-U) 
      IF (U .EQ. 0.0) GO TO 100
      CALL GRAT1(B,Z,R,P,Q,EPS)
C
      V = 0.25*(1.0/NU)**2
      T2 = 0.25*LNX*LNX
      L = W/U
      J = Q/R
      SUM = J
      T = 1.0
      CN = 1.0
      N2 = 0.0
      DO 22 N = 1,30
         BP2N = B + N2
         J = (BP2N*(BP2N + 1.0)*J + (Z + BP2N + 1.0)*T)*V
         N2 = N2 + 2.0
         T = T*T2
         CN = CN/(N2*(N2 + 1.0))
         C(N) = CN
         S = 0.0
         IF (N .EQ. 1) GO TO 21
            NM1 = N - 1
            COEF = B - N
            DO 20 I = 1,NM1
               S = S + COEF*C(I)*D(N-I) 
   20          COEF = COEF + B
   21    D(N) = BM1*CN + S/N
         DJ = D(N)*J
         SUM = SUM + DJ
         IF (SUM .LE. 0.0) GO TO 100
         IF (ABS(DJ) .LE. EPS*(SUM + L)) GO TO 30 
   22 CONTINUE
C
C                    ADD THE RESULTS TO W
C
   30 IERR = 0
      W = W + U*SUM 
      RETURN
C
C               THE EXPANSION CANNOT BE COMPUTED
C
  100 IERR = 1
      RETURN
      END 
      SUBROUTINE GRAT1 (A,X,R,P,Q,EPS)
      REAL J, L
C-----------------------------------------------------------------------
C        EVALUATION OF THE INCOMPLETE GAMMA RATIO FUNCTIONS 
C                      P(A,X) AND Q(A,X)
C
C     IT IS ASSUMED THAT A .LE. 1.  EPS IS THE TOLERANCE TO BE USED.
C     THE INPUT ARGUMENT R HAS THE VALUE E**(-X)*X**A/GAMMA(A).
C-----------------------------------------------------------------------
      IF (A*X .EQ. 0.0) GO TO 130
      IF (A .EQ. 0.5) GO TO 120
      IF (X .LT. 1.1) GO TO 10
      GO TO 50
C
C             TAYLOR SERIES FOR P(A,X)/X**A
C
   10 AN = 3.0
      C = X
      SUM = X/(A + 3.0)
      TOL = 0.1*EPS/(A + 1.0) 
   11    AN = AN + 1.0
         C = -C*(X/AN)
         T = C/(A + AN)
         SUM = SUM + T
         IF (ABS(T) .GT. TOL) GO TO 11
      J = A*X*((SUM/6.0 - 0.5/(A + 2.0))*X + 1.0/(A + 1.0)) 
C
      Z = A*ALOG(X) 
      H = GAM1(A)
      G = 1.0 + H
      IF (X .LT. 0.25) GO TO 20
         IF (A .LT. X/2.59) GO TO 40
         GO TO 30
   20 IF (Z .GT. -.13394) GO TO 40
C
   30 W = EXP(Z)
      P = W*G*(0.5 + (0.5 - J))
      Q = 0.5 + (0.5 - P)
      RETURN
C
   40 L = REXP(Z)
      W = 0.5 + (0.5 + L)
      Q = (W*J - L)*G - H
      IF (Q .LT. 0.0) GO TO 110
      P = 0.5 + (0.5 - Q)
      RETURN
C
C              CONTINUED FRACTION EXPANSION
C
   50 A2NM1 = 1.0
      A2N = 1.0
      B2NM1 = X
      B2N = X + (1.0 - A)
      C = 1.0
   51    A2NM1 = X*A2N + C*A2NM1
         B2NM1 = X*B2N + C*B2NM1
         AM0 = A2NM1/B2NM1
         C = C + 1.0
         CMA = C - A
         A2N = A2NM1 + CMA*A2N
         B2N = B2NM1 + CMA*B2N
         AN0 = A2N/B2N
         IF (ABS(AN0 - AM0) .GE. EPS*AN0) GO TO 51
      Q = R*AN0
      P = 0.5 + (0.5 - Q)
      RETURN
C
C                SPECIAL CASES
C
  100 P = 0.0
      Q = 1.0
      RETURN
C
  110 P = 1.0
      Q = 0.0
      RETURN
C
  120 IF (X .GE. 0.25) GO TO 121
      P = ERF(SQRT(X))
      Q = 0.5 + (0.5 - P)
      RETURN
  121 Q = ERFC1(0,SQRT(X))
      P = 0.5 + (0.5 - Q)
      RETURN
C
  130 IF (X .LE. A) GO TO 100 
      GO TO 110
      END 
      REAL FUNCTION BASYM(A, B, LAMBDA, EPS)
C-----------------------------------------------------------------------
C     ASYMPTOTIC EXPANSION FOR IX(A,B) FOR LARGE A AND B.
C     LAMBDA = (A + B)*Y - B  AND EPS IS THE TOLERANCE USED.
C     IT IS ASSUMED THAT LAMBDA IS NONNEGATIVE AND THAT
C     A AND B ARE GREATER THAN OR EQUAL TO 15.
C-----------------------------------------------------------------------
      REAL J0, J1, LAMBDA
      REAL A0(21), B0(21), C(21), D(21) 
C------------------------
C     ****** NUM IS THE MAXIMUM VALUE THAT N CAN TAKE IN THE DO LOOP
C            ENDING AT STATEMENT 50. IT IS REQUIRED THAT NUM BE EVEN. 
C            THE ARRAYS A0, B0, C, D HAVE DIMENSION NUM + 1.
C
                      DATA NUM/20/
C------------------------
C     E0 = 2/SQRT(PI)
C     E1 = 2**(-3/2)
C------------------------
      DATA E0/1.12837916709551/, E1/.353553390593274/
C------------------------
      BASYM = 0.0
      IF (A .GE. B) GO TO 10
         H = A/B
         R0 = 1.0/(1.0 + H)
         R1 = (B - A)/B
         W0 = 1.0/SQRT(A*(1.0 + H))
         GO TO 20
   10 H = B/A
      R0 = 1.0/(1.0 + H)
      R1 = (B - A)/A
      W0 = 1.0/SQRT(B*(1.0 + H))
C
   20 F = A*RLOG1(-LAMBDA/A) + B*RLOG1(LAMBDA/B)
      T = EXP(-F)
      IF (T .EQ. 0.0) RETURN
      Z0 = SQRT(F)
      Z = 0.5*(Z0/E1)
      Z2 = F + F
C
      A0(1) = (2.0/3.0)*R1
      C(1) = - 0.5*A0(1)
      D(1) = - C(1) 
      J0 = (0.5/E0)*ERFC1(1,Z0)
      J1 = E1
      SUM = J0 + D(1)*W0*J1
C
      S = 1.0
      H2 = H*H
      HN = 1.0
      W = W0
      ZNM1 = Z
      ZN = Z2
      DO 50 N = 2, NUM, 2
         HN = H2*HN 
         A0(N) = 2.0*R0*(1.0 + H*HN)/(N + 2.0)
         NP1 = N + 1
         S = S + HN 
         A0(NP1) = 2.0*R1*S/(N + 3.0)
C
         DO 41 I = N, NP1
         R = -0.5*(I + 1.0)
         B0(1) = R*A0(1)
         DO 31 M = 2, I
            BSUM = 0.0
            MM1 = M - 1
            DO 30 J = 1, MM1
               MMJ = M - J
   30          BSUM = BSUM + (J*R - MMJ)*A0(J)*B0(MMJ)
   31       B0(M) = R*A0(M) + BSUM/M
         C(I) = B0(I)/(I + 1.0)
C
         DSUM = 0.0 
         IM1 = I - 1
         DO 40 J = 1, IM1
            IMJ = I - J
   40       DSUM = DSUM + D(IMJ)*C(J)
   41    D(I) = -(DSUM + C(I))
C
         J0 = E1*ZNM1 + (N - 1.0)*J0
         J1 = E1*ZN + N*J1
         ZNM1 = Z2*ZNM1
         ZN = Z2*ZN 
         W = W0*W
         T0 = D(N)*W*J0
         W = W0*W
         T1 = D(NP1)*W*J1
         SUM = SUM + (T0 + T1)
         IF ((ABS(T0) + ABS(T1)) .LE. EPS*SUM) GO TO 60
   50    CONTINUE
C
   60 U = EXP(-BCORR(A,B))
      BASYM = E0*T*U*SUM
      RETURN
      END 
      REAL FUNCTION SPMPAR (I)
C-----------------------------------------------------------------------
C
C     SPMPAR PROVIDES THE SINGLE PRECISION MACHINE CONSTANTS FOR
C     THE COMPUTER BEING USED. IT IS ASSUMED THAT THE ARGUMENT
C     I IS AN INTEGER HAVING ONE OF THE VALUES 1, 2, OR 3. IF THE
C     SINGLE PRECISION ARITHMETIC BEING USED HAS M BASE B DIGITS AND
C     ITS SMALLEST AND LARGEST EXPONENTS ARE EMIN AND EMAX, THEN
C
C        SPMPAR(1) = B**(1 - M), THE MACHINE PRECISION,
C
C        SPMPAR(2) = B**(EMIN - 1), THE SMALLEST MAGNITUDE, 
C
C        SPMPAR(3) = B**EMAX*(1 - B**(-M)), THE LARGEST MAGNITUDE.
C
C-----------------------------------------------------------------------
C     WRITTEN BY
C        ALFRED H. MORRIS, JR.
C        NAVAL SURFACE WARFARE CENTER
C        DAHLGREN VIRGINIA
C-----------------------------------------------------------------------
      INTEGER EMIN, EMAX
C
      IF (I .GT. 1) GO TO 10
         B = IPMPAR(4)
         M = IPMPAR(5)
         SPMPAR = B**(1 - M)
         RETURN
C
   10 IF (I .GT. 2) GO TO 20
         B = IPMPAR(4)
         EMIN = IPMPAR(6)
         ONE = FLOAT(1)
         BINV = ONE/B
         W = B**(EMIN + 2)
         SPMPAR = ((W * BINV) * BINV) * BINV
         RETURN
C
   20 IBETA = IPMPAR(4)
      M = IPMPAR(5) 
      EMAX = IPMPAR(7)
C
      B = IBETA
      BM1 = IBETA - 1
      ONE = FLOAT(1)
      Z = B**(M - 1)
      W = ((Z - ONE)*B + BM1)/(B*Z)
C
      Z = B**(EMAX - 2)
      SPMPAR = ((W * Z) * B) * B
      RETURN
      END 
      REAL FUNCTION EXPARG (L)
C-------------------------------------------------------------------- 
C     IF L = 0 THEN  EXPARG(L) = THE LARGEST POSITIVE W FOR WHICH
C     EXP(W) CAN BE COMPUTED. 
C
C     IF L IS NONZERO THEN  EXPARG(L) = THE LARGEST NEGATIVE W FOR
C     WHICH THE COMPUTED VALUE OF EXP(W) IS NONZERO.
C
C     NOTE... ONLY AN APPROXIMATE VALUE FOR EXPARG(L) IS NEEDED.
C-------------------------------------------------------------------- 
      INTEGER B
      REAL LNB
C
      B = IPMPAR(4) 
      IF (B .NE. 2) GO TO 10
         LNB = .69314718055995
         GO TO 50
   10 IF (B .NE. 8) GO TO 20
         LNB = 2.0794415416798
         GO TO 50
   20 IF (B .NE. 16) GO TO 30 
         LNB = 2.7725887222398
         GO TO 50
   30 LNB = ALOG(FLOAT(B))
C
   50 IF (L .EQ. 0) GO TO 60
         M = IPMPAR(6) - 1
         EXPARG = 0.99999 * (M * LNB)
         RETURN
   60 M = IPMPAR(7) 
      EXPARG = 0.99999 * (M * LNB)
      RETURN
      END 
      REAL FUNCTION ESUM (MU, X)
C-----------------------------------------------------------------------
C                    EVALUATION OF EXP(MU + X)
C-----------------------------------------------------------------------
      IF (X .GT. 0.0) GO TO 10
C
      IF (MU .LT. 0) GO TO 20 
         W = MU + X 
         IF (W .GT. 0.0) GO TO 20
         ESUM = EXP(W)
         RETURN
C
   10 IF (MU .GT. 0) GO TO 20 
         W = MU + X 
         IF (W .LT. 0.0) GO TO 20
         ESUM = EXP(W)
         RETURN
C
   20 W = MU
      ESUM = EXP(W)*EXP(X)
      RETURN
      END 
      REAL FUNCTION REXP (X)
C-----------------------------------------------------------------------
C            EVALUATION OF THE FUNCTION EXP(X) - 1
C-----------------------------------------------------------------------
      DATA P1/ .914041914819518E-09/, P2/ .238082361044469E-01/,
     *     Q1/-.499999999085958E+00/, Q2/ .107141568980644E+00/,
     *     Q3/-.119041179760821E-01/, Q4/ .595130811860248E-03/
C-----------------------
      IF (ABS(X) .GT. 0.15) GO TO 10
      REXP = X*(((P2*X + P1)*X + 1.0)/((((Q4*X + Q3)*X + Q2)*X
     *                 + Q1)*X + 1.0))
      RETURN
C
   10 W = EXP(X)
      IF (X .GT. 0.0) GO TO 20
         REXP = (W - 0.5) - 0.5
         RETURN
   20 REXP = W*(0.5 + (0.5 - 1.0/W))
      RETURN
      END 
      REAL FUNCTION ALNREL(A) 
C-----------------------------------------------------------------------
C            EVALUATION OF THE FUNCTION LN(1 + A) 
C-----------------------------------------------------------------------
      DATA P1/-.129418923021993E+01/, P2/.405303492862024E+00/,
     *     P3/-.178874546012214E-01/
      DATA Q1/-.162752256355323E+01/, Q2/.747811014037616E+00/,
     *     Q3/-.845104217945565E-01/
C--------------------------
      IF (ABS(A) .GT. 0.375) GO TO 10
      T = A/(A + 2.0)
      T2 = T*T
      W = (((P3*T2 + P2)*T2 + P1)*T2 + 1.0)/
     *    (((Q3*T2 + Q2)*T2 + Q1)*T2 + 1.0)
      ALNREL = 2.0*T*W
      RETURN
C
   10 X = 1.D0 + DBLE(A)
      ALNREL = ALOG(X)
      RETURN
      END 
      REAL FUNCTION RLOG1(X)
C-----------------------------------------------------------------------
C             EVALUATION OF THE FUNCTION X - LN(1 + X)
C-----------------------------------------------------------------------
      DATA A/.566749439387324E-01/
      DATA B/.456512608815524E-01/
C------------------------
      DATA P0/ .333333333333333E+00/, P1/-.224696413112536E+00/,
     *     P2/ .620886815375787E-02/
      DATA Q1/-.127408923933623E+01/, Q2/ .354508718369557E+00/
C------------------------
      IF (X .LT. -0.39 .OR. X .GT. 0.57) GO TO 100
      IF (X .LT. -0.18) GO TO 10
      IF (X .GT.  0.18) GO TO 20
C
C              ARGUMENT REDUCTION
C
      H = X
      W1 = 0.0
      GO TO 30
C
   10 H = DBLE(X) + 0.3D0
      H = H/0.7
      W1 = A - H*0.3
      GO TO 30
C
   20 H = 0.75D0*DBLE(X) - 0.25D0
      W1 = B + H/3.0
C
C               SERIES EXPANSION
C
   30 R = H/(H + 2.0)
      T = R*R
      W = ((P2*T + P1)*T + P0)/((Q2*T + Q1)*T + 1.0)
      RLOG1 = 2.0*T*(1.0/(1.0 - R) - R*W) + W1
      RETURN
C
C
  100 W = (X + 0.5) + 0.5
      RLOG1 = X - ALOG(W)
      RETURN
      END 
      REAL FUNCTION ERF (X)
C-----------------------------------------------------------------------
C             EVALUATION OF THE REAL ERROR FUNCTION
C-----------------------------------------------------------------------
      REAL A(5),B(3),P(8),Q(8),R(5),S(4)
C-------------------------
      DATA C /.564189583547756/
C-------------------------
      DATA A(1) /.771058495001320E-04/, A(2)/-.133733772997339E-02/,
     *     A(3) /.323076579225834E-01/, A(4) /.479137145607681E-01/,
     *     A(5) /.128379167095513E+00/
      DATA B(1) /.301048631703895E-02/, B(2) /.538971687740286E-01/,
     *     B(3) /.375795757275549E+00/
C-------------------------
      DATA P(1)/-1.36864857382717E-07/, P(2) /5.64195517478974E-01/,
     *     P(3) /7.21175825088309E+00/, P(4) /4.31622272220567E+01/,
     *     P(5) /1.52989285046940E+02/, P(6) /3.39320816734344E+02/,
     *     P(7) /4.51918953711873E+02/, P(8) /3.00459261020162E+02/
      DATA Q(1) /1.00000000000000E+00/, Q(2) /1.27827273196294E+01/,
     *     Q(3) /7.70001529352295E+01/, Q(4) /2.77585444743988E+02/,
     *     Q(5) /6.38980264465631E+02/, Q(6) /9.31354094850610E+02/,
     *     Q(7) /7.90950925327898E+02/, Q(8) /3.00459260956983E+02/
C-------------------------
      DATA R(1) /2.10144126479064E+00/, R(2) /2.62370141675169E+01/,
     *     R(3) /2.13688200555087E+01/, R(4) /4.65807828718470E+00/,
     *     R(5) /2.82094791773523E-01/
      DATA S(1) /9.41537750555460E+01/, S(2) /1.87114811799590E+02/,
     *     S(3) /9.90191814623914E+01/, S(4) /1.80124575948747E+01/
C-------------------------
      AX = ABS(X)
      IF (AX .GT. 0.5) GO TO 10
      T = X*X
      TOP = ((((A(1)*T + A(2))*T + A(3))*T + A(4))*T + A(5)) + 1.0
      BOT = ((B(1)*T + B(2))*T + B(3))*T + 1.0
      ERF = X*(TOP/BOT)
      RETURN
C
   10 IF (AX .GT. 4.0) GO TO 20
      TOP = ((((((P(1)*AX + P(2))*AX + P(3))*AX + P(4))*AX + P(5))*AX 
     *                    + P(6))*AX + P(7))*AX + P(8)
      BOT = ((((((Q(1)*AX + Q(2))*AX + Q(3))*AX + Q(4))*AX + Q(5))*AX 
     *                    + Q(6))*AX + Q(7))*AX + Q(8)
      ERF = 0.5 + (0.5 - EXP(-X*X)*TOP/BOT)
      IF (X .LT. 0.0) ERF = -ERF
      RETURN
C
   20 IF (AX .GE. 5.8) GO TO 30
      X2 = X*X
      T = 1.0/X2
      TOP = (((R(1)*T + R(2))*T + R(3))*T + R(4))*T + R(5)
      BOT = (((S(1)*T + S(2))*T + S(3))*T + S(4))*T + 1.0
      ERF = (C - TOP/(X2*BOT)) / AX
      ERF = 0.5 + (0.5 - EXP(-X2)*ERF)
      IF (X .LT. 0.0) ERF = -ERF
      RETURN
C
   30 ERF = SIGN(1.0,X)
      RETURN
      END 
      REAL FUNCTION ERFC1 (IND, X)
C-----------------------------------------------------------------------
C         EVALUATION OF THE COMPLEMENTARY ERROR FUNCTION
C
C          ERFC1(IND,X) = ERFC(X)            IF IND = 0
C          ERFC1(IND,X) = EXP(X*X)*ERFC(X)   OTHERWISE
C-----------------------------------------------------------------------
      REAL A(5),B(3),P(8),Q(8),R(5),S(4)
      DOUBLE PRECISION W
C-------------------------
      DATA C /.564189583547756/
C-------------------------
      DATA A(1) /.771058495001320E-04/, A(2)/-.133733772997339E-02/,
     *     A(3) /.323076579225834E-01/, A(4) /.479137145607681E-01/,
     *     A(5) /.128379167095513E+00/
      DATA B(1) /.301048631703895E-02/, B(2) /.538971687740286E-01/,
     *     B(3) /.375795757275549E+00/
C-------------------------
      DATA P(1)/-1.36864857382717E-07/, P(2) /5.64195517478974E-01/,
     *     P(3) /7.21175825088309E+00/, P(4) /4.31622272220567E+01/,
     *     P(5) /1.52989285046940E+02/, P(6) /3.39320816734344E+02/,
     *     P(7) /4.51918953711873E+02/, P(8) /3.00459261020162E+02/
      DATA Q(1) /1.00000000000000E+00/, Q(2) /1.27827273196294E+01/,
     *     Q(3) /7.70001529352295E+01/, Q(4) /2.77585444743988E+02/,
     *     Q(5) /6.38980264465631E+02/, Q(6) /9.31354094850610E+02/,
     *     Q(7) /7.90950925327898E+02/, Q(8) /3.00459260956983E+02/
C-------------------------
      DATA R(1) /2.10144126479064E+00/, R(2) /2.62370141675169E+01/,
     *     R(3) /2.13688200555087E+01/, R(4) /4.65807828718470E+00/,
     *     R(5) /2.82094791773523E-01/
      DATA S(1) /9.41537750555460E+01/, S(2) /1.87114811799590E+02/,
     *     S(3) /9.90191814623914E+01/, S(4) /1.80124575948747E+01/
C-------------------------
C
C                     ABS(X) .LE. 0.5
C
      AX = ABS(X)
      IF (AX .GT. 0.5) GO TO 10
      T = X*X
      TOP = ((((A(1)*T + A(2))*T + A(3))*T + A(4))*T + A(5)) + 1.0
      BOT = ((B(1)*T + B(2))*T + B(3))*T + 1.0
      ERFC1 = 0.5 + (0.5 - X*(TOP/BOT)) 
      IF (IND .NE. 0) ERFC1 = EXP(T) * ERFC1
      RETURN
C
C                  0.5 .LT. ABS(X) .LE. 4
C
   10 IF (AX .GT. 4.0) GO TO 20
      TOP = ((((((P(1)*AX + P(2))*AX + P(3))*AX + P(4))*AX + P(5))*AX 
     *                    + P(6))*AX + P(7))*AX + P(8)
      BOT = ((((((Q(1)*AX + Q(2))*AX + Q(3))*AX + Q(4))*AX + Q(5))*AX 
     *                    + Q(6))*AX + Q(7))*AX + Q(8)
      ERFC1 = TOP/BOT
      GO TO 40
C
C                      ABS(X) .GT. 4
C
   20 IF (X .LE. -5.6) GO TO 50
      IF (IND .NE. 0) GO TO 30
      IF (X .GT. 100.0) GO TO 60
      IF (X*X .GT. -EXPARG(1)) GO TO 60 
C
   30 T = (1.0/X)**2
      TOP = (((R(1)*T + R(2))*T + R(3))*T + R(4))*T + R(5)
      BOT = (((S(1)*T + S(2))*T + S(3))*T + S(4))*T + 1.0
      ERFC1 = (C - T*TOP/BOT)/AX
C
C                      FINAL ASSEMBLY
C
   40 IF (IND .EQ. 0) GO TO 41
         IF (X .LT. 0.0) ERFC1 = 2.0*EXP(X*X) - ERFC1
         RETURN
   41 W = DBLE(X)*DBLE(X)
      T = W
      E = W - DBLE(T)
      ERFC1 = ((0.5 + (0.5 - E)) * EXP(-T)) * ERFC1
      IF (X .LT. 0.0) ERFC1 = 2.0 - ERFC1
      RETURN
C
C             LIMIT VALUE FOR LARGE NEGATIVE X
C
   50 ERFC1 = 2.0
      IF (IND .NE. 0) ERFC1 = 2.0*EXP(X*X)
      RETURN
C
C             LIMIT VALUE FOR LARGE POSITIVE X
C                       WHEN IND = 0
C
   60 ERFC1 = 0.0
      RETURN
      END 
      REAL FUNCTION GAM1(A)
C     ------------------------------------------------------------------
C     COMPUTATION OF 1/GAMMA(A+1) - 1  FOR -0.5 .LE. A .LE. 1.5
C     ------------------------------------------------------------------
      REAL P(7), Q(5), R(9)
C     -------------------
      DATA P(1)/ .577215664901533E+00/, P(2)/-.409078193005776E+00/,
     *     P(3)/-.230975380857675E+00/, P(4)/ .597275330452234E-01/,
     *     P(5)/ .766968181649490E-02/, P(6)/-.514889771323592E-02/,
     *     P(7)/ .589597428611429E-03/
C     -------------------
      DATA Q(1)/ .100000000000000E+01/, Q(2)/ .427569613095214E+00/,
     *     Q(3)/ .158451672430138E+00/, Q(4)/ .261132021441447E-01/,
     *     Q(5)/ .423244297896961E-02/
C     -------------------
      DATA R(1)/-.422784335098468E+00/, R(2)/-.771330383816272E+00/,
     *     R(3)/-.244757765222226E+00/, R(4)/ .118378989872749E+00/,
     *     R(5)/ .930357293360349E-03/, R(6)/-.118290993445146E-01/,
     *     R(7)/ .223047661158249E-02/, R(8)/ .266505979058923E-03/,
     *     R(9)/-.132674909766242E-03/
C     -------------------
      DATA S1  / .273076135303957E+00/, S2  / .559398236957378E-01/
C     -------------------
      T = A
      D = A - 0.5
      IF (D .GT. 0.0) T = D - 0.5
      IF (T) 30,10,20
C
   10 GAM1 = 0.0
      RETURN
C
   20 TOP = (((((P(7)*T + P(6))*T + P(5))*T + P(4))*T + P(3))*T
     *                  + P(2))*T + P(1)
      BOT = (((Q(5)*T + Q(4))*T + Q(3))*T + Q(2))*T + 1.0
      W = TOP/BOT
      IF (D .GT. 0.0) GO TO 21
         GAM1 = A*W 
         RETURN
   21 GAM1 = (T/A)*((W - 0.5) - 0.5)
      RETURN
C
   30 TOP = (((((((R(9)*T + R(8))*T + R(7))*T + R(6))*T + R(5))*T
     *                    + R(4))*T + R(3))*T + R(2))*T + R(1)
      BOT = (S2*T + S1)*T + 1.0
      W = TOP/BOT
      IF (D .GT. 0.0) GO TO 31
         GAM1 = A*((W + 0.5) + 0.5)
         RETURN
   31 GAM1 = T*W/A
      RETURN
      END 
      REAL FUNCTION GAMLN1 (A)
C-----------------------------------------------------------------------
C     EVALUATION OF LN(GAMMA(1 + A)) FOR -0.2 .LE. A .LE. 1.25
C-----------------------------------------------------------------------
      DATA P0/ .577215664901533E+00/, P1/ .844203922187225E+00/,
     *     P2/-.168860593646662E+00/, P3/-.780427615533591E+00/,
     *     P4/-.402055799310489E+00/, P5/-.673562214325671E-01/,
     *     P6/-.271935708322958E-02/
      DATA Q1/ .288743195473681E+01/, Q2/ .312755088914843E+01/,
     *     Q3/ .156875193295039E+01/, Q4/ .361951990101499E+00/,
     *     Q5/ .325038868253937E-01/, Q6/ .667465618796164E-03/
C----------------------
      DATA R0/.422784335098467E+00/,  R1/.848044614534529E+00/,
     *     R2/.565221050691933E+00/,  R3/.156513060486551E+00/,
     *     R4/.170502484022650E-01/,  R5/.497958207639485E-03/
      DATA S1/.124313399877507E+01/,  S2/.548042109832463E+00/,
     *     S3/.101552187439830E+00/,  S4/.713309612391000E-02/,
     *     S5/.116165475989616E-03/
C----------------------
      IF (A .GE. 0.6) GO TO 10
      W = ((((((P6*A + P5)*A + P4)*A + P3)*A + P2)*A + P1)*A + P0)/
     *    ((((((Q6*A + Q5)*A + Q4)*A + Q3)*A + Q2)*A + Q1)*A + 1.0)
      GAMLN1 = -A*W 
      RETURN
C
   10 X = (A - 0.5) - 0.5
      W = (((((R5*X + R4)*X + R3)*X + R2)*X + R1)*X + R0)/
     *    (((((S5*X + S4)*X + S3)*X + S2)*X + S1)*X + 1.0)
      GAMLN1 = X*W
      RETURN
      END 
      REAL FUNCTION PSI(XX)
C---------------------------------------------------------------------
C
C                 EVALUATION OF THE DIGAMMA FUNCTION
C
C                           ----------- 
C
C     PSI(XX) IS ASSIGNED THE VALUE 0 WHEN THE DIGAMMA FUNCTION CANNOT
C     BE COMPUTED.
C
C     THE MAIN COMPUTATION INVOLVES EVALUATION OF RATIONAL CHEBYSHEV
C     APPROXIMATIONS PUBLISHED IN MATH. COMP. 27, 123-127(1973) BY
C     CODY, STRECOK AND THACHER.
C
C---------------------------------------------------------------------
C     PSI WAS WRITTEN AT ARGONNE NATIONAL LABORATORY FOR THE FUNPACK
C     PACKAGE OF SPECIAL FUNCTION SUBROUTINES. PSI WAS MODIFIED BY
C     A.H. MORRIS (NSWC).
C---------------------------------------------------------------------
      REAL P1(7), P2(4), Q1(6), Q2(4)
      DOUBLE PRECISION DX0
C---------------------------------------------------------------------
C
C     PIOV4 = PI/4
C     DX0 = ZERO OF PSI TO EXTENDED PRECISION
C
C---------------------------------------------------------------------
      DATA PIOV4/.785398163397448E0/
      DATA DX0/1.461632144968362341262659542325721325D0/
C---------------------------------------------------------------------
C
C     COEFFICIENTS FOR RATIONAL APPROXIMATION OF
C     PSI(X) / (X - X0),  0.5 .LE. X .LE. 3.0
C
C---------------------------------------------------------------------
      DATA P1(1)/.895385022981970E-02/,  P1(2)/.477762828042627E+01/, 
     *     P1(3)/.142441585084029E+03/,  P1(4)/.118645200713425E+04/, 
     *     P1(5)/.363351846806499E+04/,  P1(6)/.413810161269013E+04/, 
     *     P1(7)/.130560269827897E+04/
      DATA Q1(1)/.448452573429826E+02/,  Q1(2)/.520752771467162E+03/, 
     *     Q1(3)/.221000799247830E+04/,  Q1(4)/.364127349079381E+04/, 
     *     Q1(5)/.190831076596300E+04/,  Q1(6)/.691091682714533E-05/
C---------------------------------------------------------------------
C
C     COEFFICIENTS FOR RATIONAL APPROXIMATION OF
C     PSI(X) - LN(X) + 1 / (2*X),  X .GT. 3.0
C
C---------------------------------------------------------------------
      DATA P2(1)/-.212940445131011E+01/, P2(2)/-.701677227766759E+01/,
     *     P2(3)/-.448616543918019E+01/, P2(4)/-.648157123766197E+00/ 
      DATA Q2(1)/ .322703493791143E+02/, Q2(2)/ .892920700481861E+02/,
     *     Q2(3)/ .546117738103215E+02/, Q2(4)/ .777788548522962E+01/ 
C---------------------------------------------------------------------
C
C     MACHINE DEPENDENT CONSTANTS ...
C
C        XMAX1  = THE SMALLEST POSITIVE FLOATING POINT CONSTANT
C                 WITH ENTIRELY INTEGER REPRESENTATION.  ALSO USED
C                 AS NEGATIVE OF LOWER BOUND ON ACCEPTABLE NEGATIVE
C                 ARGUMENTS AND AS THE POSITIVE ARGUMENT BEYOND WHICH 
C                 PSI MAY BE REPRESENTED AS ALOG(X).
C
C        XSMALL = ABSOLUTE ARGUMENT BELOW WHICH PI*COTAN(PI*X)
C                 MAY BE REPRESENTED BY 1/X.
C
C---------------------------------------------------------------------
      XMAX1 = IPMPAR(3)
      XMAX1 = AMIN1(XMAX1, 1.0/SPMPAR(1))
      XSMALL = 1.E-9
C---------------------------------------------------------------------
      X = XX
      AUG = 0.0E0
      IF (X .GE. 0.5E0) GO TO 200
C---------------------------------------------------------------------
C     X .LT. 0.5,  USE REFLECTION FORMULA
C     PSI(1-X) = PSI(X) + PI * COTAN(PI*X)
C---------------------------------------------------------------------
      IF (ABS(X) .GT. XSMALL) GO TO 100 
      IF (X .EQ. 0.0E0) GO TO 400
C---------------------------------------------------------------------
C     0 .LT. ABS(X) .LE. XSMALL.  USE 1/X AS A SUBSTITUTE
C     FOR  PI*COTAN(PI*X)
C---------------------------------------------------------------------
      AUG = -1.0E0 / X
      GO TO 150
C---------------------------------------------------------------------
C     REDUCTION OF ARGUMENT FOR COTAN
C---------------------------------------------------------------------
  100 W = - X
      SGN = PIOV4
      IF (W .GT. 0.0E0) GO TO 120
      W = - W
      SGN = -SGN
C---------------------------------------------------------------------
C     MAKE AN ERROR EXIT IF X .LE. -XMAX1
C---------------------------------------------------------------------
  120 IF (W .GE. XMAX1) GO TO 400
      NQ = INT(W)
      W = W - FLOAT(NQ)
      NQ = INT(W*4.0E0)
      W = 4.0E0 * (W - FLOAT(NQ) * .25E0)
C---------------------------------------------------------------------
C     W IS NOW RELATED TO THE FRACTIONAL PART OF  4.0 * X.
C     ADJUST ARGUMENT TO CORRESPOND TO VALUES IN FIRST
C     QUADRANT AND DETERMINE SIGN
C---------------------------------------------------------------------
      N = NQ / 2
      IF ((N+N) .NE. NQ) W = 1.0E0 - W
      Z = PIOV4 * W 
      M = N / 2
      IF ((M+M) .NE. N) SGN = - SGN
C---------------------------------------------------------------------
C     DETERMINE FINAL VALUE FOR  -PI*COTAN(PI*X)
C---------------------------------------------------------------------
      N = (NQ + 1) / 2
      M = N / 2
      M = M + M
      IF (M .NE. N) GO TO 140 
C---------------------------------------------------------------------
C     CHECK FOR SINGULARITY
C---------------------------------------------------------------------
      IF (Z .EQ. 0.0E0) GO TO 400
C---------------------------------------------------------------------
C     USE COS/SIN AS A SUBSTITUTE FOR COTAN, AND
C     SIN/COS AS A SUBSTITUTE FOR TAN
C---------------------------------------------------------------------
      AUG = SGN * ((COS(Z) / SIN(Z)) * 4.0E0)
      GO TO 150
  140 AUG = SGN * ((SIN(Z) / COS(Z)) * 4.0E0)
  150 X = 1.0E0 - X 
  200 IF (X .GT. 3.0E0) GO TO 300
C---------------------------------------------------------------------
C     0.5 .LE. X .LE. 3.0
C---------------------------------------------------------------------
      DEN = X
      UPPER = P1(1) * X
C
      DO 210 I = 1, 5
         DEN = (DEN + Q1(I)) * X
         UPPER = (UPPER + P1(I+1)) * X
  210 CONTINUE
C
      DEN = (UPPER + P1(7)) / (DEN + Q1(6))
      XMX0 = DBLE(X) - DX0
      PSI = DEN * XMX0 + AUG
      RETURN
C---------------------------------------------------------------------
C     IF X .GE. XMAX1, PSI = LN(X)
C---------------------------------------------------------------------
  300 IF (X .GE. XMAX1) GO TO 350
C---------------------------------------------------------------------
C     3.0 .LT. X .LT. XMAX1
C---------------------------------------------------------------------
      W = 1.0E0 / (X * X)
      DEN = W
      UPPER = P2(1) * W
C
      DO 310 I = 1, 3
         DEN = (DEN + Q2(I)) * W
         UPPER = (UPPER + P2(I+1)) * W
  310 CONTINUE
C
      AUG = UPPER / (DEN + Q2(4)) - 0.5E0 / X + AUG
  350 PSI = AUG + ALOG(X)
      RETURN
C---------------------------------------------------------------------
C     ERROR RETURN
C---------------------------------------------------------------------
  400 PSI = 0.0E0
      RETURN
      END 
      REAL FUNCTION BETALN (A0, B0)
C-----------------------------------------------------------------------
C     EVALUATION OF THE LOGARITHM OF THE BETA FUNCTION
C-----------------------------------------------------------------------
C     E = 0.5*LN(2*PI)
C--------------------------
      DATA E /.918938533204673/
C--------------------------
      A = AMIN1(A0,B0)
      B = AMAX1(A0,B0)
      IF (A .GE. 8.0) GO TO 60
      IF (A .GE. 1.0) GO TO 20
C-----------------------------------------------------------------------
C                   PROCEDURE WHEN A .LT. 1
C-----------------------------------------------------------------------
      IF (B .GE. 8.0) GO TO 10
         BETALN = GAMLN(A) + (GAMLN(B) - GAMLN(A + B))
         RETURN
   10 BETALN = GAMLN(A) + ALGDIV(A,B)
      RETURN
C-----------------------------------------------------------------------
C                PROCEDURE WHEN 1 .LE. A .LT. 8
C-----------------------------------------------------------------------
   20 IF (A .GT. 2.0) GO TO 30
      IF (B .GT. 2.0) GO TO 21
         BETALN = GAMLN(A) + GAMLN(B) - GSUMLN(A,B)
         RETURN
   21 W = 0.0
      IF (B .LT. 8.0) GO TO 40
         BETALN = GAMLN(A) + ALGDIV(A,B)
         RETURN
C
C                REDUCTION OF A WHEN B .LE. 1000
C
   30 IF (B .GT. 1000.0) GO TO 50
      N = A - 1.0
      W = 1.0
      DO 31 I = 1,N 
         A = A - 1.0
         H = A/B
         W = W * (H/(1.0 + H))
   31 CONTINUE
      W = ALOG(W)
      IF (B .LT. 8.0) GO TO 40
      BETALN = W + GAMLN(A) + ALGDIV(A,B)
      RETURN
C
C                 REDUCTION OF B WHEN B .LT. 8
C
   40 N = B - 1.0
      Z = 1.0
      DO 41 I = 1,N 
         B = B - 1.0
         Z = Z * (B/(A + B))
   41 CONTINUE
      BETALN = W + ALOG(Z) + (GAMLN(A) + (GAMLN(B) - GSUMLN(A,B)))
      RETURN
C
C                REDUCTION OF A WHEN B .GT. 1000
C
   50 N = A - 1.0
      W = 1.0
      DO 51 I = 1,N 
         A = A - 1.0
         W = W * (A/(1.0 + A/B))
   51 CONTINUE
      BETALN = (ALOG(W) - N*ALOG(B)) + (GAMLN(A) + ALGDIV(A,B))
      RETURN
C-----------------------------------------------------------------------
C                   PROCEDURE WHEN A .GE. 8
C-----------------------------------------------------------------------
   60 W = BCORR(A,B)
      H = A/B
      C = H/(1.0 + H)
      U = -(A - 0.5)*ALOG(C)
      V = B*ALNREL(H)
      IF (U .LE. V) GO TO 61
         BETALN = (((-0.5*ALOG(B) + E) + W) - V) - U
         RETURN
   61 BETALN = (((-0.5*ALOG(B) + E) + W) - U) - V 
      RETURN
      END 
      REAL FUNCTION GSUMLN (A, B)
C-----------------------------------------------------------------------
C          EVALUATION OF THE FUNCTION LN(GAMMA(A + B))
C          FOR 1 .LE. A .LE. 2  AND  1 .LE. B .LE. 2
C-----------------------------------------------------------------------
      X = DBLE(A) + DBLE(B) - 2.D0
      IF (X .GT. 0.25) GO TO 10
         GSUMLN = GAMLN1(1.0 + X)
         RETURN
   10 IF (X .GT. 1.25) GO TO 20
         GSUMLN = GAMLN1(X) + ALNREL(X) 
         RETURN
   20 GSUMLN = GAMLN1(X - 1.0) + ALOG(X*(1.0 + X))
      RETURN
      END 
      REAL FUNCTION BCORR (A0, B0)
C-----------------------------------------------------------------------
C
C     EVALUATION OF  DEL(A0) + DEL(B0) - DEL(A0 + B0)  WHERE
C     LN(GAMMA(A)) = (A - 0.5)*LN(A) - A + 0.5*LN(2*PI) + DEL(A).
C     IT IS ASSUMED THAT A0 .GE. 8 AND B0 .GE. 8. 
C
C-----------------------------------------------------------------------
      DATA C0/.833333333333333E-01/, C1/-.277777777760991E-02/,
     *     C2/.793650666825390E-03/, C3/-.595202931351870E-03/,
     *     C4/.837308034031215E-03/, C5/-.165322962780713E-02/
C------------------------
      A = AMIN1(A0, B0)
      B = AMAX1(A0, B0)
C
      H = A/B
      C = H/(1.0 + H)
      X = 1.0/(1.0 + H)
      X2 = X*X
C
C                SET SN = (1 - X**N)/(1 - X)
C
      S3 = 1.0 + (X + X2)
      S5 = 1.0 + (X + X2*S3)
      S7 = 1.0 + (X + X2*S5)
      S9 = 1.0 + (X + X2*S7)
      S11 = 1.0 + (X + X2*S9) 
C
C                SET W = DEL(B) - DEL(A + B)
C
      T = (1.0/B)**2
      W = ((((C5*S11*T + C4*S9)*T + C3*S7)*T + C2*S5)*T + C1*S3)*T + C0
      W = W*(C/B)
C
C                   COMPUTE  DEL(A) + W 
C
      T = (1.0/A)**2
      BCORR = (((((C5*T + C4)*T + C3)*T + C2)*T + C1)*T + C0)/A + W
      RETURN
      END 
      REAL FUNCTION ALGDIV (A, B)
C-----------------------------------------------------------------------
C
C     COMPUTATION OF LN(GAMMA(B)/GAMMA(A+B)) WHEN B .GE. 8
C
C                         --------
C
C     IN THIS ALGORITHM, DEL(X) IS THE FUNCTION DEFINED BY
C     LN(GAMMA(X)) = (X - 0.5)*LN(X) - X + 0.5*LN(2*PI) + DEL(X).
C
C-----------------------------------------------------------------------
      DATA C0/.833333333333333E-01/, C1/-.277777777760991E-02/,
     *     C2/.793650666825390E-03/, C3/-.595202931351870E-03/,
     *     C4/.837308034031215E-03/, C5/-.165322962780713E-02/
C------------------------
      IF (A .LE. B) GO TO 10
         H = B/A
         C = 1.0/(1.0 + H)
         X = H/(1.0 + H)
         D = A + (B - 0.5)
         GO TO 20
   10 H = A/B
      C = H/(1.0 + H)
      X = 1.0/(1.0 + H)
      D = B + (A - 0.5)
C
C                SET SN = (1 - X**N)/(1 - X)
C
   20 X2 = X*X
      S3 = 1.0 + (X + X2)
      S5 = 1.0 + (X + X2*S3)
      S7 = 1.0 + (X + X2*S5)
      S9 = 1.0 + (X + X2*S7)
      S11 = 1.0 + (X + X2*S9) 
C
C                SET W = DEL(B) - DEL(A + B)
C
      T = (1.0/B)**2
      W = ((((C5*S11*T + C4*S9)*T + C3*S7)*T + C2*S5)*T + C1*S3)*T + C0
      W = W*(C/B)
C
C                    COMBINE THE RESULTS
C
      U = D*ALNREL(A/B)
      V = A*(ALOG(B) - 1.0)
      IF (U .LE. V) GO TO 30
         ALGDIV = (W - V) - U 
         RETURN
   30 ALGDIV = (W - U) - V
      RETURN
      END 
      REAL FUNCTION GAMLN (A) 
C-----------------------------------------------------------------------
C            EVALUATION OF LN(GAMMA(A)) FOR POSITIVE A
C-----------------------------------------------------------------------
C     WRITTEN BY ALFRED H. MORRIS
C          NAVAL SURFACE WARFARE CENTER 
C          DAHLGREN, VIRGINIA 
C--------------------------
C     D = 0.5*(LN(2*PI) - 1)
C--------------------------
      DATA D/.418938533204673/
C--------------------------
      DATA C0/.833333333333333E-01/, C1/-.277777777760991E-02/,
     *     C2/.793650666825390E-03/, C3/-.595202931351870E-03/,
     *     C4/.837308034031215E-03/, C5/-.165322962780713E-02/
C-----------------------------------------------------------------------
      IF (A .GT. 0.8) GO TO 10
         GAMLN = GAMLN1(A) - ALOG(A)
         RETURN
   10 IF (A .GT. 2.25) GO TO 20
         T = (A - 0.5) - 0.5
         GAMLN = GAMLN1(T)
         RETURN
C
   20 IF (A .GE. 10.0) GO TO 30
      N = A - 1.25
      T = A
      W = 1.0
      DO 21 I = 1,N 
         T = T - 1.0
   21    W = T*W
      GAMLN = GAMLN1(T - 1.0) + ALOG(W) 
      RETURN
C
   30 T = (1.0/A)**2
      W = (((((C5*T + C4)*T + C3)*T + C2)*T + C1)*T + C0)/A 
      GAMLN = (D + W) + (A - 0.5)*(ALOG(A) - 1.0) 
      END 
      INTEGER FUNCTION IPMPAR (I)
C-----------------------------------------------------------------------
C
C     IPMPAR PROVIDES THE INTEGER MACHINE CONSTANTS FOR THE COMPUTER
C     THAT IS USED. IT IS ASSUMED THAT THE ARGUMENT I IS AN INTEGER
C     HAVING ONE OF THE VALUES 1-10. IPMPAR(I) HAS THE VALUE ...
C
C  INTEGERS.
C
C     ASSUME INTEGERS ARE REPRESENTED IN THE N-DIGIT, BASE-A FORM
C
C               SIGN ( X(N-1)*A**(N-1) + ... + X(1)*A + X(0) )
C
C               WHERE 0 .LE. X(I) .LT. A FOR I=0,...,N-1.
C
C     IPMPAR(1) = A, THE BASE.
C
C     IPMPAR(2) = N, THE NUMBER OF BASE-A DIGITS. 
C
C     IPMPAR(3) = A**N - 1, THE LARGEST MAGNITUDE.
C
C  FLOATING-POINT NUMBERS.
C
C     IT IS ASSUMED THAT THE SINGLE AND DOUBLE PRECISION FLOATING
C     POINT ARITHMETICS HAVE THE SAME BASE, SAY B, AND THAT THE
C     NONZERO NUMBERS ARE REPRESENTED IN THE FORM 
C
C               SIGN (B**E) * (X(1)/B + ... + X(M)/B**M)
C
C               WHERE X(I) = 0,1,...,B-1 FOR I=1,...,M,
C               X(1) .GE. 1, AND EMIN .LE. E .LE. EMAX.
C
C     IPMPAR(4) = B, THE BASE.
C
C  SINGLE-PRECISION 
C
C     IPMPAR(5) = M, THE NUMBER OF BASE-B DIGITS. 
C
C     IPMPAR(6) = EMIN, THE SMALLEST EXPONENT E.
C
C     IPMPAR(7) = EMAX, THE LARGEST EXPONENT E.
C
C  DOUBLE-PRECISION 
C
C     IPMPAR(8) = M, THE NUMBER OF BASE-B DIGITS. 
C
C     IPMPAR(9) = EMIN, THE SMALLEST EXPONENT E.
C
C     IPMPAR(10) = EMAX, THE LARGEST EXPONENT E.
C
C-----------------------------------------------------------------------
C
C     TO DEFINE THIS FUNCTION FOR THE COMPUTER BEING USED, ACTIVATE
C     THE DATA STATMENTS FOR THE COMPUTER BY REMOVING THE C FROM
C     COLUMN 1. (ALL THE OTHER DATA STATEMENTS SHOULD HAVE C IN
C     COLUMN 1.)
C
C-----------------------------------------------------------------------
C
C     IPMPAR IS AN ADAPTATION OF THE FUNCTION I1MACH, WRITTEN BY
C     P.A. FOX, A.D. HALL, AND N.L. SCHRYER (BELL LABORATORIES).
C     IPMPAR WAS FORMED BY A.H. MORRIS (NSWC). THE CONSTANTS ARE
C     FROM BELL LABORATORIES, NSWC, AND OTHER SOURCES.
C
C-----------------------------------------------------------------------
      INTEGER IMACH(10)
C
C     MACHINE CONSTANTS FOR AMDAHL MACHINES.
C
C     DATA IMACH( 1) /   2 /
C     DATA IMACH( 2) /  31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /  16 /
C     DATA IMACH( 5) /   6 /
C     DATA IMACH( 6) / -64 /
C     DATA IMACH( 7) /  63 /
C     DATA IMACH( 8) /  14 /
C     DATA IMACH( 9) / -64 /
C     DATA IMACH(10) /  63 /
C
C     MACHINE CONSTANTS FOR THE AT&T 3B SERIES, AT&T
C     PC 7300, AND AT&T 6300. 
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE BURROUGHS 1700 SYSTEM.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   33 / 
C     DATA IMACH( 3) / 8589934591 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   24 / 
C     DATA IMACH( 6) / -256 / 
C     DATA IMACH( 7) /  255 / 
C     DATA IMACH( 8) /   60 / 
C     DATA IMACH( 9) / -256 / 
C     DATA IMACH(10) /  255 / 
C
C     MACHINE CONSTANTS FOR THE BURROUGHS 5700 SYSTEM.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   39 / 
C     DATA IMACH( 3) / 549755813887 /
C     DATA IMACH( 4) /    8 / 
C     DATA IMACH( 5) /   13 / 
C     DATA IMACH( 6) /  -50 / 
C     DATA IMACH( 7) /   76 / 
C     DATA IMACH( 8) /   26 / 
C     DATA IMACH( 9) /  -50 / 
C     DATA IMACH(10) /   76 / 
C
C     MACHINE CONSTANTS FOR THE BURROUGHS 6700/7700 SYSTEMS.
C
C     DATA IMACH( 1) /      2 /
C     DATA IMACH( 2) /     39 /
C     DATA IMACH( 3) / 549755813887 /
C     DATA IMACH( 4) /      8 /
C     DATA IMACH( 5) /     13 /
C     DATA IMACH( 6) /    -50 /
C     DATA IMACH( 7) /     76 /
C     DATA IMACH( 8) /     26 /
C     DATA IMACH( 9) / -32754 /
C     DATA IMACH(10) /  32780 /
C
C     MACHINE CONSTANTS FOR THE CDC 6000/7000 SERIES
C     60 BIT ARITHMETIC, AND THE CDC CYBER 995 64 BIT
C     ARITHMETIC (NOS OPERATING SYSTEM).
C
      DATA IMACH( 1) /    2 / 
      DATA IMACH( 2) /   48 / 
      DATA IMACH( 3) / 281474976710655 /
      DATA IMACH( 4) /    2 / 
      DATA IMACH( 5) /   48 / 
      DATA IMACH( 6) / -974 / 
      DATA IMACH( 7) / 1070 / 
      DATA IMACH( 8) /   95 / 
      DATA IMACH( 9) / -926 / 
      DATA IMACH(10) / 1070 / 
C
C     MACHINE CONSTANTS FOR THE CDC CYBER 995 64 BIT
C     ARITHMETIC (NOS/VE OPERATING SYSTEM).
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    63 /
C     DATA IMACH( 3) / 9223372036854775807 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    48 /
C     DATA IMACH( 6) / -4096 /
C     DATA IMACH( 7) /  4095 /
C     DATA IMACH( 8) /    96 /
C     DATA IMACH( 9) / -4096 /
C     DATA IMACH(10) /  4095 /
C
C     MACHINE CONSTANTS FOR THE CRAY 1, XMP, 2, AND 3.
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    63 /
C     DATA IMACH( 3) / 9223372036854775807 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    47 /
C     DATA IMACH( 6) / -8189 /
C     DATA IMACH( 7) /  8190 /
C     DATA IMACH( 8) /    94 /
C     DATA IMACH( 9) / -8099 /
C     DATA IMACH(10) /  8190 /
C
C     MACHINE CONSTANTS FOR THE DATA GENERAL ECLIPSE S/200. 
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   15 / 
C     DATA IMACH( 3) / 32767 /
C     DATA IMACH( 4) /   16 / 
C     DATA IMACH( 5) /    6 / 
C     DATA IMACH( 6) /  -64 / 
C     DATA IMACH( 7) /   63 / 
C     DATA IMACH( 8) /   14 / 
C     DATA IMACH( 9) /  -64 / 
C     DATA IMACH(10) /   63 / 
C
C     MACHINE CONSTANTS FOR THE HARRIS 220.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   23 / 
C     DATA IMACH( 3) / 8388607 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   23 / 
C     DATA IMACH( 6) / -127 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   38 / 
C     DATA IMACH( 9) / -127 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE HONEYWELL 600/6000
C     AND DPS 8/70 SERIES.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   35 / 
C     DATA IMACH( 3) / 34359738367 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   27 / 
C     DATA IMACH( 6) / -127 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   63 / 
C     DATA IMACH( 9) / -127 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE HP 2100 
C     3 WORD DOUBLE PRECISION OPTION WITH FTN4
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   15 / 
C     DATA IMACH( 3) / 32767 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   23 / 
C     DATA IMACH( 6) / -128 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   39 / 
C     DATA IMACH( 9) / -128 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE HP 2100 
C     4 WORD DOUBLE PRECISION OPTION WITH FTN4
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   15 / 
C     DATA IMACH( 3) / 32767 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   23 / 
C     DATA IMACH( 6) / -128 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   55 / 
C     DATA IMACH( 9) / -128 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE HP 9000.
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -126 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE IBM 360/370 SERIES,
C     THE ICL 2900, THE ITEL AS/6, THE XEROX SIGMA
C     5/7/9 AND THE SEL SYSTEMS 85/86.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   31 / 
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /   16 / 
C     DATA IMACH( 5) /    6 / 
C     DATA IMACH( 6) /  -64 / 
C     DATA IMACH( 7) /   63 / 
C     DATA IMACH( 8) /   14 / 
C     DATA IMACH( 9) /  -64 / 
C     DATA IMACH(10) /   63 / 
C
C     MACHINE CONSTANTS FOR THE IBM PC. 
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE MACINTOSH II - ABSOFT
C     MACFORTRAN II.
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE MICROVAX - VMS FORTRAN.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   31 / 
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   24 / 
C     DATA IMACH( 6) / -127 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   56 / 
C     DATA IMACH( 9) / -127 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE PDP-10 (KA PROCESSOR).
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   35 / 
C     DATA IMACH( 3) / 34359738367 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   27 / 
C     DATA IMACH( 6) / -128 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   54 / 
C     DATA IMACH( 9) / -101 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE PDP-10 (KI PROCESSOR).
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   35 / 
C     DATA IMACH( 3) / 34359738367 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   27 / 
C     DATA IMACH( 6) / -128 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   62 / 
C     DATA IMACH( 9) / -128 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE PDP-11 FORTRAN SUPPORTING
C     32-BIT INTEGER ARITHMETIC.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   31 / 
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   24 / 
C     DATA IMACH( 6) / -127 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   56 / 
C     DATA IMACH( 9) / -127 / 
C     DATA IMACH(10) /  127 / 
C
C     MACHINE CONSTANTS FOR THE SEQUENT BALANCE 8000.
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE SILICON GRAPHICS IRIS-4D
C     SERIES (MIPS R3000 PROCESSOR).
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE SUN 3.
C
C     DATA IMACH( 1) /     2 /
C     DATA IMACH( 2) /    31 /
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /     2 /
C     DATA IMACH( 5) /    24 /
C     DATA IMACH( 6) /  -125 /
C     DATA IMACH( 7) /   128 /
C     DATA IMACH( 8) /    53 /
C     DATA IMACH( 9) / -1021 /
C     DATA IMACH(10) /  1024 /
C
C     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   35 / 
C     DATA IMACH( 3) / 34359738367 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   27 / 
C     DATA IMACH( 6) / -128 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   60 / 
C     DATA IMACH( 9) /-1024 / 
C     DATA IMACH(10) / 1023 / 
C
C     MACHINE CONSTANTS FOR THE VAX 11/780.
C
C     DATA IMACH( 1) /    2 / 
C     DATA IMACH( 2) /   31 / 
C     DATA IMACH( 3) / 2147483647 /
C     DATA IMACH( 4) /    2 / 
C     DATA IMACH( 5) /   24 / 
C     DATA IMACH( 6) / -127 / 
C     DATA IMACH( 7) /  127 / 
C     DATA IMACH( 8) /   56 / 
C     DATA IMACH( 9) / -127 / 
C     DATA IMACH(10) /  127 / 
C
      IPMPAR = IMACH(I)
      RETURN
      END 
