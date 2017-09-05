#include "Score.h"
#include "fltk/std_lib_facilities_4.h"

istream& operator>>(istream& is, Score& s)
// This assumes the format: Initials / Score
{
	Score ss;
	if (is >> ss.initials >> ss.score) {
		s = ss;
		return is;
	} 
	else 
		return is;
}

ostream& operator<<(ostream& os, Score& s)
// Write out: Initials / Score
{
	return os << s.initials << " " << s.score;
}

Score::Score(string init,int sc) {
	initials = init;
	score = sc;
}

void Score::get_scores(string file_name, Vector<Score>& sv)
// This reads the high score data from file and puts it into Score vector
{
	ifstream ifs {file_name};
	if (!ifs) error("can't open ",file_name);

	for (Score s; ifs >> s; ) sv.push_back(s);
	if (ifs.eof()) return;

	ifs.clear();
}

bool Score::compare_scores(const Score& a, const Score& b)
// It is the function to aid in sorting of Score vector (sorts in descending order)
{
	return a.score > b.score;
}

void Score::sort_scores(Vector<Score>& sv)
// It sorts Score vector based on score
{
	sort(sv.begin(),sv.end(),compare_scores);
}

void Score::write_out_scores(string file_name, Vector<Score>& sv)
// It writes score vector out to file
{
	ofstream ofs {file_name};
	if (!ofs) error("can't open ",file_name);

	for (int i = 0, n = sv.size(); i < n; ++i)
		ofs << sv[i] << '\n';
}