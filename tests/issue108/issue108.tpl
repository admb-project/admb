DATA_SECTION
  init_6darray inarray6(1,1,1,2,1,3,1,4,1,5,1,6) //Need to implement type data_6array
  init_7darray inarray7(1,1,1,2,1,3,1,4,1,5,1,6,1,7) //Need to implement type data_7array
  6darray array6(1,1,1,2,1,3,1,4,1,5,1,6)
  7darray array7(1,1,1,2,1,3,1,4,1,5,1,6,1,7)

PARAMETER_SECTION
  6darray array6(1,1,1,2,1,3,1,4,1,5,1,6)
  7darray array7(1,1,1,2,1,3,1,4,1,5,1,6,1,7)
  
  init_number x
  objective_function_value f

PROCEDURE_SECTION
  {
    int index = 0;
    for (int i6 = 1; i6 <= 1; ++i6)
      for (int i5 = 1; i5 <= 2; ++i5)
        for (int i4 = 1; i4 <= 3; ++i4)
          for (int i3 = 1; i3 <= 4; ++i3)
            for (int i2 = 1; i2 <= 5; ++i2)
              for (int i1 = 1; i1 <= 6; ++i1)
                if (inarray6(i6, i5, i4, i3, i2, i1) != index++) cout << __FILE__ << endl;
    for (int i7 = 1; i7 <= 1; ++i7)
      for (int i6 = 1; i6 <= 2; ++i6)
        for (int i5 = 1; i5 <= 3; ++i5)
          for (int i4 = 1; i4 <= 4; ++i4)
            for (int i3 = 1; i3 <= 5; ++i3)
              for (int i2 = 1; i2 <= 6; ++i2)
                for (int i1 = 1; i1 <= 7; ++i1)
                  if (inarray7(i7, i6, i5, i4, i3, i2, i1) != index++) cout << __FILE__ << endl;
  }
  f=x;
