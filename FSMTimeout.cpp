
#include "FSMTimeout.h"
FSMTimeout::FSMTimeout(const FSMTimeout& m)
{
	flag = m.flag;
	number_of_states = m.number_of_states;
	number_of_inputs = m.number_of_inputs;
	number_of_outputs = m.number_of_outputs;
	number_of_transitions = m.number_of_transitions;
	initial_state = m.initial_state;
	timeoutsystem = new timeout[number_of_states];
	transitionsystem = new transitionTime[number_of_transitions];

	for (unsigned int i = 0; i < number_of_transitions; i++)
		transitionsystem[i] = m.transitionsystem[i];

	for (unsigned int i = 0; i < number_of_states; i++)
		timeoutsystem[i] = m.timeoutsystem[i];
}
FSMTimeout& FSMTimeout::operator=(const FSMTimeout& m)
{
	if (transitionsystem != NULL) delete[] transitionsystem;
	if (timeoutsystem != NULL) delete[] timeoutsystem;
	flag = m.flag;
	number_of_states = m.number_of_states;
	number_of_inputs = m.number_of_inputs;
	number_of_outputs = m.number_of_outputs;
	number_of_transitions = m.number_of_transitions;
	initial_state = m.initial_state;
	timeoutsystem = new timeout[number_of_states];
	transitionsystem = new transitionTime[number_of_transitions];

	for (unsigned int i = 0; i < number_of_transitions; i++)
		transitionsystem[i] = m.transitionsystem[i];

	for (unsigned int i = 0; i < number_of_states; i++)
		timeoutsystem[i] = m.timeoutsystem[i];
	return *this;
}
void FSMTimeout::In(istream &f)
{
	if (transitionsystem != NULL) delete[]transitionsystem;
	if (timeoutsystem != NULL) delete[]timeoutsystem;
	char c;
	unsigned int cn = 0;
	f >> c >> this->flag;
	f >> c >> this->number_of_states;
	f >> c >> this->number_of_inputs;
	f >> c >> this->number_of_outputs;
	f >> c >> c >> this->initial_state;
	f >> c >> this->number_of_transitions;
	transitionsystem = new transitionTime[this->number_of_transitions];
	timeoutsystem = new timeout[number_of_states];
	for (unsigned int i = 0; i < this->number_of_transitions; i++)
	{
		f >> transitionsystem[i].state1;
		f >> transitionsystem[i].input;
		f >> transitionsystem[i].state2;
		f >> transitionsystem[i].output;
		f >> cn;
	}
	int n = 0;
	for (unsigned int i = 0; i < this->number_of_states; i++)
	{
		f >> cn;
		f >> n;
		timeoutsystem[i].t = n;
		f >> timeoutsystem[i].state2;
	}
};
void FSMTimeout::Out(ostream& f)
{
	f << "F " << this->flag;
	f << "\ns " << this->number_of_states << "\ni " << this->number_of_inputs << "\no " << this->number_of_outputs;
	f << "\nn0 " << this->initial_state << "\np " << this->number_of_transitions;
	f << endl;
	for (unsigned int i = 0; i < this->number_of_transitions; i++)
	{
		f << transitionsystem[i].state1 << " ";
		f << transitionsystem[i].input << " ";
		f << transitionsystem[i].state2 << " ";
		f << transitionsystem[i].output << " ";
		f << 0;
		f << endl;
	}
	for (unsigned int i = 0; i < this->number_of_states; i++)
	{
		f << i << " ";
		f << timeoutsystem[i].t << " ";
		f << timeoutsystem[i].state2 << " ";
		f << endl;
	}
};

bool FSMTimeout::coverage(time_sequence seq, LongVector tr_vec, LongVector time_vec)
{
	int s = 0, ct = 0;
	for (unsigned int i = 0; i < seq.length; i++)
	{
		
		ct = seq.time[i];
		if ((time_vec[s])&&(ct>=1)) return true;
		while (ct >= timeoutsystem[s].t)
		{
			if (time_vec[s]) return true;

			ct = ct - timeoutsystem[s].t;
			s = timeoutsystem[s].state2;
		}
		if (tr_vec[s*number_of_inputs + seq.sym[i]]) return true;

		s = transitionsystem[s*number_of_inputs + seq.sym[i]].state2;
	}
	return false;
}