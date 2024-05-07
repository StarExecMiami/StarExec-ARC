fof(a1,assumption,a1,
    introduced(assumption) ).

fof(a2,assumption,a2,
    introduced(assumption) ).

fof(as_imply_b,axiom,(a1 & a2) => b).

fof(b_implies_c,axiom,b => c).

fof(c_implies_d,axiom,c  => d).

% fof(d_implies_e,axiom,d => e).

fof(a2_implies_b,plain,a2 => b,
    inference(mp,[status(thm),assumptions([a1])],[a1,as_imply_b]) ).

fof(b,plain,b,
    inference(mp,[status(thm),assumptions([a1,a2])],[a2,a2_implies_b]) ).

fof(b_implies_d,plain,b => d,
    inference(mp,[status(thm)],[b_implies_c,c_implies_d]) ).

%fof(a1_implies_a2_implies_e,plain,a1 => (a2 => e),
%    inference(mp_discharge,
%[mp_discharge(discharge,[a1]),status(thm)],
%[inference(crazy,
%           [crazy(discharge,[a2]),status(thm),assumptions([a1])],
%           [b,b_implies_d,a2]),
% d_implies_e,a1]) ).

fof(a2_implies_d,plain,a2 => d,
    inference(crazy,[crazy(discharge,[a2]),status(thm),assumptions([a1])],
[b,b_implies_d,a2]) ).

fof(prove_a2_implies_d,conjecture,a2 => d).

fof(reutation,plain,$false,
    inference(big_step,[status(thm),assumptions([a1])],
[a2_implies_d,prove_a2_implies_d]) ).

% fof(a1_implies_a2_implies_e,plain,a1 => (a2 => e),
%     inference(mp_discharge,[mp_discharge(discharge,[a1]),status(thm)],
% [d_implies_e,a2_implies_d,a1])  ).
