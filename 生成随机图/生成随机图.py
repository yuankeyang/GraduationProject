# coding=gbk
# ����ͼ�����ڽӱ��ʽ�洢Ϊ�ļ�
import networkx as nx
import matplotlib.pyplot as plt

G = nx.gnp_random_graph(100, 0.1)
nx.write_adjlist(G,"../test.adjlist")
plt.figure(1)
nx.draw(G)
plt.show()