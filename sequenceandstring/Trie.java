package hellocomrade.happycoding

import java.util.ArrayList;
import java.util.List;
import java.util.function.IntFunction;


public class NumberTrie<T> {
    private int size;
    private final NumberTrieNode<T> root;
    private final IntFunction<? extends T> arrayGenerator;

    public static NumberTrie<char[]> CharacterNumberTrie() {
        return new NumberTrie<>(char[]::new, 10);
    }

    public static NumberTrie<int[]> BitsetNumberTrie(int capacity) {
        return new NumberTrie<>(int[]::new, capacity) {
            @Override
            public void add(char[] digitId, int[] payload, int length) {
                var node = addAndGet(digitId);
                if(!node.initialized)
                    node.initPayload();
                for(int i : payload) {
                    node.payload[i >> 5] = 1 << (i & 0x1F);
                    ++node.used;
                }
            }
        };
    }

    public static int estimateBitSetCapacity(int max) {
        return max / Integer.SIZE + 1;
    }

    public NumberTrie(IntFunction<? extends T> generator, int capacity) {
        root = new NumberTrieNode<>(generator, capacity);
        root.reset();
        arrayGenerator = generator;
    }

    public NumberTrieNode<T> addAndGet(char[] digitId) {
        if(digitId == null || digitId.length < 1)
            return null;
        NumberTrieNode<T> node = root;
        short j;
        for (char c : digitId) {
            j = (short) (c - '0');
            node = node.set(j);
        }
        return node;
    }

    public void add(char[] digitId, T payload, int length) {
        if(digitId == null || digitId.length < 1)
            return;
        NumberTrieNode<T> node = addAndGet(digitId);
        if(length < 1) {// if T is not an array
            node.payload = payload;
            node.used = 1;
        }
        else {
            if(!node.initialized)
                node.initPayload();
            if(node.length - node.used < length) {
                node.length = Math.max(node.length * 4, node.used + length);
                T copy = arrayGenerator.apply(node.length);
                System.arraycopy(node.payload, 0, copy, 0, node.used);
                node.payload = copy;
            }
            System.arraycopy(payload, 0, node.payload, node.used, length);
            node.used += length;
            node.sizeAt(length);
        }
        ++size;
    }

    public TrieNodePayload<T> get(char[] digitId) {
        if(digitId == null || digitId.length < 1)
            return null;
        NumberTrieNode<T> node = root;
        int i = 0;
        short k = 0;
        while(node != null && i < digitId.length) {
            k = (short)(digitId[i++] - '0');
            if(node.get(k))
                node = node.buckets.get(k);
            else
                node = null;
        }
        return node != null
                && i == digitId.length
                && node.hasPayload()
                ? new TrieNodePayload<>(node.payload, node.size)
                : null;
    }

    public int getSize() {
        return size;
    }

    public record TrieNodePayload<T>(T payload, int[] sizes){}

    static class NumberTrieNode<T> {
        private final IntFunction<? extends T> generator;
        private final int capacity;

        public boolean initialized = false;
        public List<NumberTrieNode<T>> buckets;
        public short value;
        public T payload;
        public int length;//length of payload if payload is []
        public int used;//used length of payload if payload is []
        public int[] size;//size of each segment on the payload if payload is [], shouldn't have more than 10 segments per payload

        public NumberTrieNode(IntFunction<? extends T> generator1, int size) {
            generator = generator1;
            capacity = size;
        }

        public void reset() {
            used = 0;
            buckets = new ArrayList<>(10);
            for(int i = 0; i < 10; ++i)
                buckets.add(null);
            size = new int[10];
        }

        public void initPayload() {
            length = capacity;
            payload = generator.apply(capacity);
            initialized = true;
        }

        public NumberTrieNode<T> set(short i) {
            if(i < 0 || i > 9)
                throw new IllegalArgumentException("0 - 9 only.");
            if(buckets.get(i) == null) {
                buckets.set(i, new NumberTrieNode<>(generator, capacity));
                buckets.get(i).reset();
            }
            var b = buckets.get(i);
            b.value = i;
            return b;
        }

        public boolean get(short i) {
            if(i < 0 || i > 9)
                throw new IllegalArgumentException("0 - 9 only.");
            return buckets != null && buckets.get(i) != null;
        }

        public void sizeAt(int sz) {
            int i = 0;
            for(;i < 10 && size[i] != 0; ++i);
            if(i < 10)
                size[i] = sz;
            else
                throw new IllegalArgumentException("10 segment per payload[i].");
        }

        public boolean hasPayload() {
            return payload != null && used > 0;
        }
    }
}
