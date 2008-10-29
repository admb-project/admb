        inline AD_LONG_INT& elem(int i) { return(v[i]); }
#ifdef USE_CONST
        inline _CONST AD_LONG_INT& elem(int i) _CONST { return(v[i]); }
#endif
