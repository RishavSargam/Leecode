class Solution:
    def smallestSubsequence(self, s):
        # Store the last index where each character appears
        last = {c: i for i, c in enumerate(s)}
        stk = []
        visited = set()

        for i, c in enumerate(s):
            # If the character is already in the subsequence, skip it
            if c in visited:
                continue

            # Pop larger characters from the stack if they appear later
            while stk and stk[-1] > c and last[stk[-1]] > i:
                visited.remove(stk.pop())

            # Add the current character to the stack
            stk.append(c)
            visited.add(c)

        return "".join(stk)
