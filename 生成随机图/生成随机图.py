# coding=gbk
# ����ͼ�����ڽӱ��ʽ�洢Ϊ�ļ�
import networkx as nx
import matplotlib.pyplot as plt

G = nx.gnp_random_graph(200, 0.1)
nx.write_adjlist(G,"../test1.adjlist")
plt.figure(1)
nx.draw(G)
plt.show()