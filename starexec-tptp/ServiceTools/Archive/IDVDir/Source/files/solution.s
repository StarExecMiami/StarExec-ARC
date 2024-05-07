cnf(113,plain,
    ( has_unit__dfg(skc2,long__dfg) ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(115,plain,
    ( has_unit__dfg(skc3,geolat__dfg) ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(121,plain,
    ( cos__dfg(skc3) = rtb_Product3_mm_idx__dfg ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(122,plain,
    ( sin__dfg(skc2) = rtb_sine_idx_0__dfg ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(123,plain,
    ( cos__dfg(skc2) = rtb_Product3_mm_idx_0__dfg ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(124,plain,
    ( sin__dfg(skc3) = rtb_sine_idx__dfg ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(146,plain,
    ( times__dfg(U,V) = times__dfg(V,U) ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(218,plain,
    ( ~ has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(cg_in__dfg,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx_0__dfg,rtb_sine_idx__dfg))),n1__dfg,times__dfg(tptp_float_minus_1_0__dfg,rtb_sine_idx_0__dfg)),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_Product3_mm_idx_0__dfg))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,rtb_sine_idx_0__dfg))),n4__dfg,rtb_Product3_mm_idx_0__dfg),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_sine_idx_0__dfg))),n6__dfg,rtb_Product3_mm_idx__dfg),n7__dfg,times__dfg(tptp_float_0_0__dfg,rtb_Product3_mm_idx__dfg)),n8__dfg,times__dfg(tptp_float_minus_1_0__dfg,rtb_sine_idx__dfg)),dcm__dfg(ecef__dfg,ned__dfg)) ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(220,plain,
    ( ~ has_unit__dfg(U,geolat__dfg)
    | ~ has_unit__dfg(V,long__dfg)
    | has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(W,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(sin__dfg(U),cos__dfg(V)))),n1__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(V))),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(cos__dfg(U),cos__dfg(V)))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(sin__dfg(U),sin__dfg(V)))),n4__dfg,cos__dfg(V)),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(cos__dfg(U),sin__dfg(V)))),n6__dfg,cos__dfg(U)),n7__dfg,times__dfg(tptp_float_0_0__dfg,cos__dfg(U))),n8__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(U))),dcm__dfg(ecef__dfg,ned__dfg)) ),
    file('/tmp/SystemOnTPTP32060/SOT_5c2yrx.dfg',unknown),
    []).

cnf(246,plain,
    ( ~ has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(cg_in__dfg,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx_0__dfg,rtb_sine_idx__dfg))),n1__dfg,times__dfg(rtb_sine_idx_0__dfg,tptp_float_minus_1_0__dfg)),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_Product3_mm_idx_0__dfg))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,rtb_sine_idx_0__dfg))),n4__dfg,rtb_Product3_mm_idx_0__dfg),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_sine_idx_0__dfg))),n6__dfg,rtb_Product3_mm_idx__dfg),n7__dfg,times__dfg(rtb_Product3_mm_idx__dfg,tptp_float_0_0__dfg)),n8__dfg,times__dfg(rtb_sine_idx__dfg,tptp_float_minus_1_0__dfg)),dcm__dfg(ecef__dfg,ned__dfg)) ),
    inference(rew,[status(thm)],[146,218,theory(equality)]),
    [iquote('0:Rew:146.0,218.0,146.0,218.0,146.0,218.0')]).

cnf(248,plain,
    ( ~ has_unit__dfg(U,long__dfg)
    | has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(V,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(sin__dfg(skc3),cos__dfg(U)))),n1__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(U))),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(cos__dfg(skc3),cos__dfg(U)))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(sin__dfg(skc3),sin__dfg(U)))),n4__dfg,cos__dfg(U)),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(cos__dfg(skc3),sin__dfg(U)))),n6__dfg,cos__dfg(skc3)),n7__dfg,times__dfg(tptp_float_0_0__dfg,cos__dfg(skc3))),n8__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(skc3))),dcm__dfg(ecef__dfg,ned__dfg)) ),
    inference(res,[status(thm)],[115,220,theory(equality)]),
    [iquote('0:Res:115.0,220.1')]).

cnf(267,plain,
    ( ~ has_unit__dfg(U,long__dfg)
    | has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(V,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,cos__dfg(U)))),n1__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(U))),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,cos__dfg(U)))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,sin__dfg(U)))),n4__dfg,cos__dfg(U)),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,sin__dfg(U)))),n6__dfg,rtb_Product3_mm_idx__dfg),n7__dfg,times__dfg(tptp_float_0_0__dfg,rtb_Product3_mm_idx__dfg)),n8__dfg,times__dfg(tptp_float_minus_1_0__dfg,rtb_sine_idx__dfg)),dcm__dfg(ecef__dfg,ned__dfg)) ),
    inference(rew,[status(thm)],[121,248,124,theory(equality)]),
    [iquote('0:Rew:121.0,248.1,124.0,248.1')]).

cnf(273,plain,
    ( has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(U,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,cos__dfg(skc2)))),n1__dfg,times__dfg(tptp_float_minus_1_0__dfg,sin__dfg(skc2))),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,cos__dfg(skc2)))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,sin__dfg(skc2)))),n4__dfg,cos__dfg(skc2)),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,sin__dfg(skc2)))),n6__dfg,rtb_Product3_mm_idx__dfg),n7__dfg,times__dfg(tptp_float_0_0__dfg,rtb_Product3_mm_idx__dfg)),n8__dfg,times__dfg(tptp_float_minus_1_0__dfg,rtb_sine_idx__dfg)),dcm__dfg(ecef__dfg,ned__dfg)) ),
    inference(res,[status(thm)],[113,267,theory(equality)]),
    [iquote('0:Res:113.0,267.0')]).

cnf(284,plain,
    ( has_frame__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(tptp_update2__dfg(U,n0__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx_0__dfg,rtb_sine_idx__dfg))),n1__dfg,times__dfg(rtb_sine_idx_0__dfg,tptp_float_minus_1_0__dfg)),n2__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_Product3_mm_idx_0__dfg))),n3__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_sine_idx__dfg,rtb_sine_idx_0__dfg))),n4__dfg,rtb_Product3_mm_idx_0__dfg),n5__dfg,times__dfg(tptp_float_minus_1_0__dfg,times__dfg(rtb_Product3_mm_idx__dfg,rtb_sine_idx_0__dfg))),n6__dfg,rtb_Product3_mm_idx__dfg),n7__dfg,times__dfg(rtb_Product3_mm_idx__dfg,tptp_float_0_0__dfg)),n8__dfg,times__dfg(rtb_sine_idx__dfg,tptp_float_minus_1_0__dfg)),dcm__dfg(ecef__dfg,ned__dfg)) ),
    inference(rew,[status(thm)],[146,273,123,122,theory(equality)]),
    [iquote('0:Rew:146.0,273.0,146.0,273.0,123.0,273.0,122.0,273.0,146.0,273.0,146.0,273.0')]).

cnf(285,plain,
    ( $false ),
    inference(unc,[status(thm)],[284,246]),
    [iquote('0:UnC:284.0,246.0')]).
