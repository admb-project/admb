//========================================================================
// Example ADMB code calling ADMB2R functions to create a file containing
// an R object as output from an AD Model Builder model.
//
// This source should be included in the ADMB REPORT_SECTION. See ADMB2R
// User's Guide.  This file by Andi Stephens, revised by Mike Prager.
// Address inquiries to
// Michael Prager <mike.prager@noaa.gov> or
// Jennifer Martin <jennifer.martin@noaa.gov>
//
// This file is part of the ADMB2R distribution.
//========================================================================
// Open the output file using the AD Model Builder template name, and
// specify 6 digits of precision

open_r_file(adprogram_name + ".rdat", 6, -999);


    // Example of metadata stored in an INFO object (R list)

    open_r_info_list("info", true);
        wrt_r_item("title", "Sample Catch at Age Model");
        wrt_r_item("species", "Flack Lake Trout");
        wrt_r_item("units.len", "mm");
    close_r_info_list();


    // Example of storing scalar parameter estimates into an R list

    open_r_info_list("parms", false);
        wrt_r_item("M", M);
        wrt_r_item("avg_F", avg_F);
        wrt_r_item("pred_B", pred_B);
        wrt_r_item("log_q", log_q);
        wrt_r_item("log_popscale", log_popscale);
        wrt_r_item("Obj.fcn", f);
    close_r_info_list();


   // Example of writing a COMPLETE VECTOR object
   // NOTE: vector "ages" was declared in the DATA_SECTION for use here as:
   //   ivector ages(1,nages);

   for (int i=1;i<=nages;i++) ages(i) = (i);    //populate the ages vector
   wrt_r_complete_vector("log.sel", log_sel, ages);


    // Example of a MATRIX object with no row or column names

    open_r_matrix("F.at.age");
        wrt_r_matrix(F);
    close_r_matrix();


    // Example of a MATRIX object with row names, but no column names;
    // rows specified by constructing a series since a vector of years
    // is not a variable

    open_r_matrix("N.at.age.1");
        wrt_r_matrix(N, 2);
        wrt_r_namevector(1968, 1979);
    close_r_matrix();


    // Example of the same matrix as above object with row and column names;
    // rows specified by constructing a series since the a vector of years
    // is not a variable; columns specified by constructing a series since
    // a vector of ages isn't supplied

    open_r_matrix("N.at.age.2");
        wrt_r_matrix(N, 2, 2);
        wrt_r_namevector(1968, 1979);
        wrt_r_namevector(3, 9);
    close_r_matrix();


    // Example of a DATA FRAME object composed of two items.
    // The data frame will span 1 to the number of ages. The vectors
    // span 2 to the number of ages, so NAs will be written for the first
    // data point in the two vectors. The row names will be included,
    // similar to the matrix object just before this one.

   open_r_df("aseries", 1, nages, 2);
        wrt_r_df_col("N.pred", predicted_N);
        wrt_r_df_col("N.ratio", ratio_N);
        wrt_r_namevector(3, 9);
    close_r_df();


    // Example of a LIST object

    open_r_list("C.at.age.mats");


        // List component #1: matrix with row and column names

        open_r_matrix("Est");
            wrt_r_matrix(C, 1, 1);
        close_r_matrix();


        // List component #2: another matrix with row and column names

        open_r_matrix("Obs");
            wrt_r_matrix(obs_catch_at_age, 1, 1);
        close_r_matrix();

    close_r_list();

    wrt_r_comment("Begin testing permutations of matrix calls unused above");
    wrt_r_comment("No rownames; col names from matrix");

    open_r_matrix("Obs_catch_at_age");
        wrt_r_matrix(obs_catch_at_age,0,1);
    close_r_matrix();


    wrt_r_comment("No names, NA matrix");

    for (int i = 1; i <= nyrs; i++) {
        for (int j = 1; j<= nages; j++){
            NA[i][j] = 0;
        }
    }
    NA[1][1] = 1;
    NA[2][2] = 1;
    NA[nyrs-1][nages-1] = 1;
    NA[nyrs][nages] = 1;

    open_r_matrix("Obs_catch_at_age");
        wrt_r_matrix(obs_catch_at_age,0,0,1,NA);
    close_r_matrix();

    testcol = column(obs_catch_at_age, 1);

    wrt_r_comment("DF column from series");
    wrt_r_comment("Then obs_catch 1,3:6 shifted by one.");
    open_r_df("Series", 1966, 1970, 2);
        wrt_r_df_col("First", 5,10);
        wrt_r_df_col("Second", testcol(6,10), 1967);
        wrt_r_namevector(1,5);
    close_r_df();


// close file

close_r_file();

// End of example
