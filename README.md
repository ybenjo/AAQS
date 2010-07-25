# About
C++によるQeury Suggestion Algorithmのいくつかの実装です

## Algorithm
現状では以下のアルゴリズムを実装しています
1. Pan J, Yang H, Faloutsos C, Duygulu P. Automatic multimedia cross-modal correlation discovery.
Proceedings of the 2004 ACM SIGKDD international conference on Knowledge discovery and data mining - KDD '04. 2004:653.
Available at: http://portal.acm.org/citation.cfm?doid=1014052.1014135.
2. Deng H, King I, Lyu MR. Entropy-biased models for query representation on the click graph.
Proceedings of the 32nd international ACM SIGIR conference on Research and development in information retrieval - SIGIR '09. 2009:339.
Available at: http://portal.acm.org/citation.cfm?doid=1571941.1572001.
3. Kong H, Lyu MR, King I. A generalized Co-HITS algorithm and its application to bipartite graphs.
Proceedings of the 15th ACM SIGKDD international conference on Knowledge discovery and data mining - KDD '09. 2009:239.
Available at: http://portal.acm.org/citation.cfm?doid=1557019.1557051.
4. Mei Q, Zhou D, Church K. Query suggestion using hitting time.
Proceeding of the 17th ACM conference on Information and knowledge mining - CIKM '08. 2008:469.
Available at: http://portal.acm.org/citation.cfm?doid=1458082.1458145.

## 使い方
tr1::unordered\_mapに依存しています。
また、テストにはgoogletestを用いています。
	$make main
	$ruby ./run.rb
いくつかの引数を指定することができます
- -m:用いるアルゴリズムの選択。省略時は1。それぞれ
1 -> Random walk With Restart(RWR)
2 -> Entropy biased models
3 -> Generalized Co-HITS
4 -> hitting timeに対応。
- -t:random walkの繰り返し回数。省略時は5
- -d:サブグラフを作る際の深さ。省略時は4
- -s:出力する際の件数。省略時は10
- -e:CF-IQFに基づいて遷移確率を上書きするか。省略時はfalse。アルゴリズムが2の場合はtrueに。
- -u:Generalized Co-HITSで用いる伝播パラメータ。省略時は0.5
- -v:Generalized Co-HITSで用いる伝播パラメータ。省略時は0.5
- -c:RWR、Entropy biased modelsで用いるダンピングファクター。省略時は0.5

***File format
The delimiter is Tab.For example:
query_1\turl_1\t10
query_1\turl_2\t3
...
