//http://www.lintcode.com/en/problem/topological-sorting/
import java.util.ArrayList;
import java.util.HashMap;
public class TopologicalSort{
    public static class DirectedGraphNode {
        int label;
        ArrayList<DirectedGraphNode> neighbors;
        DirectedGraphNode(int x) { label = x; neighbors = new ArrayList<DirectedGraphNode>(); }
    };
    private void dfs(HashMap<DirectedGraphNode, Integer> map, ArrayList<DirectedGraphNode> ans, DirectedGraphNode node) {
        map.put(node, 1);
        for(DirectedGraphNode neighbor : node.neighbors) {
            if(map.get(neighbor) == 0)
                dfs(map, ans, neighbor);
        }
        ans.add(0, node);
    }
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */    
    public ArrayList<DirectedGraphNode> topSort(ArrayList<DirectedGraphNode> graph) {
        // write your code here
        HashMap<DirectedGraphNode, Integer> map = new HashMap<>();
        ArrayList<DirectedGraphNode> ans = new ArrayList<>();
        for(DirectedGraphNode node : graph)
            map.put(node, 0);
        for(DirectedGraphNode node : map.keySet())
            if(map.get(node) == 0)
                dfs(map, ans, node);
        return ans;
    }
}
