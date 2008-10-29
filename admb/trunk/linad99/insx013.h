        int& elem(int i) { return(v[i]); }
#ifdef USE_CONST
        _CONST int& elem(int i) _CONST { return(v[i]); }
#endif
