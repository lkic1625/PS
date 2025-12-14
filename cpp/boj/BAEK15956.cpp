// JAVA code.
//import java.io.BufferedReader;
//import java.io.IOException;
//import java.io.InputStreamReader;
//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.HashSet;
//import java.util.List;
//import java.util.Map;
//import java.util.Objects;
//import java.util.Set;
//
//public class Main {
//
//
//private static final String EQUAL = "==";
//private static final String NOT_EQUAL = "!=";
//private static final String AND = "&&";
//
//private static void solution() throws IOException {
//            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
////    String input = br.readLine();
//            String input = "kakaocodefestival==-20180804&&hello!=-20180804";
//            Map<String, Integer> stringConverter = new HashMap<>();
//            Map<Integer, String> integerConverter = new HashMap<>();
//
//            List<Condition> notEqualConditions = new ArrayList<>();
//            List<Condition> equalConditions = new ArrayList<>();
//
//            int counter = 0;
//            String[] result = input.split(AND);
//            UnionFind uf = new UnionFind();
//            for (String condition : result) {
//
//                String operator = EQUAL;
//                String[] temp = condition.split(EQUAL);
//                if (temp.length == 1) {
//                    temp = condition.split(NOT_EQUAL);
//                    operator = NOT_EQUAL;
//                }
//
//                String lv = temp[0];
//                String rv = temp[1];
//                if (stringConverter.get(lv) == null) {
//                    integerConverter.put(counter, lv);
//                    stringConverter.put(lv, counter++);
//                }
//
//                if (stringConverter.get(rv) == null) {
//                    integerConverter.put(counter, rv);
//                    stringConverter.put(rv, counter++);
//                }
//
//                if (operator.equals(NOT_EQUAL)) {
//                    notEqualConditions.add(new Condition(lv, operator, rv));
//                } else {
//                    equalConditions.add(new Condition(lv, operator, rv));
//                }
//            }
//
//            equalConditions.forEach(condition -> {
//                if (!Objects.equals(condition.lv, condition.rv)) {
//                    uf.merge(stringConverter.get(condition.lv), stringConverter.get(condition.rv));
//                }
//            });
//
//            StringBuffer sb = new StringBuffer();
//            for (int i = 0; i < counter; ++i) {
//                int parent = uf.find(i);
//                if (parent != i) {
//                    sb.append(integerConverter.get(parent)).append("==").append(integerConverter.get(i)).append(AND);
//                }
//            }
//
//            Set<Pair> notEqualsConditionSet = new HashSet<>();
//            notEqualConditions.forEach(condition -> {
//                int lvP = uf.find(stringConverter.get(condition.lv));
//                int rvP = uf.find(stringConverter.get(condition.rv));
//
//                if (lvP == rvP) {
//                    System.out.println("1!=1");
//                    return;
//                } else {
//                    notEqualsConditionSet.add(new Pair(lvP, rvP));
//                }
//            });
//
//            notEqualsConditionSet.forEach(pair -> {
//                sb.append(integerConverter.get(pair.lv)).append(NOT_EQUAL).append(integerConverter.get(pair.rv));
//            });
//
//            if (!sb.isEmpty()) {
//                sb.setLength(sb.length() - 2);
//            }
//
//            System.out.println(sb);
//    }
//
//public static void main(String[] args) throws IOException {
//            solution();
//    }
//
//    static class Condition {
//        String lv;
//        String operator;
//        String rv;
//
//    public Condition(String lv, String operator, String rv) {
//            this.lv = lv;
//            this.operator = operator;
//            this.rv = rv;
//        }
//    }
//
//    static class Pair {
//        int lv;
//        int rv;
//
//    public Pair(int lv, int rv) {
//            if (lv > rv) {
//                this.lv = lv;
//                this.rv = rv;
//            } else {
//                this.lv = rv;
//                this.rv = lv;
//            }
//        }
//
//        @Override
//    public int hashCode() {
//            int hash = 7;
//
//            hash = 31 * hash + lv;
//            hash = 31 * hash + rv;
//            return hash;
//        }
//
//        @Override
//    public boolean equals(Object p) {
//            if (p instanceof Pair) {
//                Pair pair = (Pair) p;
//                return (pair.lv == lv && pair.rv == rv);
//            }
//
//            return false;
//        }
//    }
//
//    static class UnionFind {
//    private int[] parent;
//
//        UnionFind() {
//            parent = new int[1000000];
//            for (int i = 0; i < 1000000; i++) {
//                parent[i] = i;
//            }
//        }
//
//        int find(int a) {
//            if (parent[a] == a) {
//                return a;
//            }
//
//            return parent[a] = find(parent[a]);
//        }
//
//        void merge(int a, int b) {
//            a = find(a);
//            b = find(b);
//
//            parent[b] = a;
//        }
//    }
//}