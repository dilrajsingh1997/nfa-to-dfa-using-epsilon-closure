#include <bits/stdc++.h>
using namespace std;
vector < vector < pair < int, set < int > > > > tr_table;
map < set < int >, bool > m;
vector < vector < pair < set < int >, set < int > > > > dfa;
set < set < int > > dfa_final_states;
int n_states, alphabet;
void epsilon_closure(int start, set < int > &tmp){
	pair < int, set < int > > pr = tr_table[start].back();
	set < int > st = pr.second;
	for(auto &it:st){
		tmp.insert(it);
		epsilon_closure(it, tmp);
	}
}
void nfa_transition(set < int > states, int alpha, set < int > &transitions){
	for(auto &it:states){
		pair < int, set < int > > pr = tr_table[it][alpha];
		transitions.insert(pr.second.begin(), pr.second.end());
	}
}
void check_final(set < int > cls, set < int > final_states){
	set < int > intersect;
	set_intersection(cls.begin(), cls.end(), final_states.begin(), final_states.end(), inserter(intersect, intersect.begin()));
	if(intersect.size()>0)
		dfa_final_states.insert(cls);
}
int main(int argc, char const *argv[]){
	cout<<"Enter the no. of states and size of alphabet set ";
	cin>>n_states>>alphabet;
	cout<<"Enter the transition table\n";
	for(int i=0;i<n_states;i++){
		vector < pair < int, set < int > > > tmp;
		cout<<"Input for state "<<i<<endl;
		for(int j=0;j<alphabet;j++){
			cout<<"\tEnter the no of states for "<<char(j+97)<<": ";
			int n_alpha;
			cin>>n_alpha;
			set < int > st;
			for(int k=0;k<n_alpha;k++){
				cout<<"\t\t";
				int temp;
				cin>>temp;
				st.insert(temp);
			}
			tmp.push_back(make_pair(j, st));
		}
		cout<<"\tEnter the no of states for epsilon ";
		int n_alpha;
		cin>>n_alpha;
		set < int > st;
		for(int k=0;k<n_alpha;k++){
			cout<<"\t\t";
			int temp;
			cin>>temp;
			st.insert(temp);
		}
		tmp.push_back(make_pair(-1, st));
		tr_table.push_back(tmp);
	}
	cout<<"Enter start state ";
	int start_state;
	cin>>start_state;
	cout<<"Enter no. of final states ";
	int f_states;
	cin>>f_states;
	cout<<"Enter final states ";
	set < int > final_states;
	for(int i=0;i<f_states;i++){
		int temp;
		cin>>temp;
		final_states.insert(temp);
	}
	int iterator = 0;
	queue < set < int > > q;
	map < set < int >, int > mp;
	set < int > cls;
	cls.insert(start_state);
	epsilon_closure(start_state, cls);
	q.push(cls);
	check_final(cls, final_states);
	while(!q.empty()){
		set < int > closure = q.front();
		q.pop();
		mp[closure] = iterator;
		iterator ++;
		vector < pair < set < int >, set < int > > > tmp;
		for(int i=0;i<alphabet;i++){
			set < int > transitions;
			nfa_transition(closure, i, transitions);
			for(auto &it:transitions){
				epsilon_closure(it, transitions);
			}
			if(!(mp.count(transitions)>0)){
				q.push(transitions);
				check_final(transitions, final_states);
			}
			tmp.push_back(make_pair(closure, transitions));
		}
		dfa.push_back(tmp);
	}
	cout<<endl<<"    ";
	for(int i=0;i<alphabet;i++)
		cout<<char(i+97)<<"  ";
	cout<<endl;
	for(int i=0;i<dfa.size();i++){
		bool print = true;
		for(int j=0;j<dfa[i].size();j++){
			pair < set < int >, set < int > > pr = dfa[i][j];
			set < int > from = pr.first;
			set < int > to = pr.second;
			if(print)
				cout<<mp[from]<<" : ";
			print = false;
			cout<<mp[to]<<"  ";
		}
		cout<<endl;
	}
	cout<<"\nFinal states\n";
	for(auto &it:dfa_final_states)
		cout<<mp[it]<<" ";
	cout<<endl<<endl;
	cout<<"Key:\n";
	map < int, set < int > > mp2;
	vector<int>v;
	for(auto&it:mp){
		v.push_back(it.second);
		set < int > mm;
		for(auto &ptr:it.first)
			mm.insert(ptr);
		mp2[it.second]=mm;
	}
	sort(v.begin(),v.end());
	for(auto&it:v){
		cout<<it<<": { ";
		for(auto&ptr:mp2[it])
			cout<<ptr<<" ";
		cout<<"}";
		cout<<endl;
	}
	return 0;
}
