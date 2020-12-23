/// Complexity: ?????
/// Tested: Not yet
inline lf simpson(lf fl, lf fr, lf fmid, lf l, lf r) {
  return (fl + fr + 4.0 * fmid) * (r - l) / 6.0;
}
lf rsimpson (lf slr, lf fl, lf fr, lf fmid, lf l, lf r) {
	lf mid = (l + r) * 0.5;
	lf fml = f((l + mid) * 0.5);
	lf fmr = f((mid + r) * 0.5);
	lf slm = simpson(fl, fmid, fml, l, mid);
	lf smr = simpson(fmid, fr, fmr, mid, r);
	if (fabs(slr - slm - smr) < eps) return slm + smr;
	return rsimpson(slm, fl, fmid, fml, l, mid) + rsimpson(smr, fmid, fr, fmr, mid, r);
}
lf integrate(lf l,lf r) {
	lf mid = (l + r) * .5, fl = f(l), fr = f(r), fmid = f(mid);
	return rsimpson(simpson(fl, fr, fmid, l, r), fl, fr, fmid, l, r);
}
