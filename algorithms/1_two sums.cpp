class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        map<int, int> hmap;
        hmap.clear();
        for (int i=0; i<nums.size(); i++)
        {
            hmap[nums[i]] = i;
        }
        for (int i=0;i<nums.size(); i++)
        {
            int number = target - nums[i];
            if (hmap.find(number) != hmap.end())
            {
                if(i<hmap[number])
                {
                    res.push_back(i);
                    res.push_back(hmap[number]);
                    return res;
                }
                if(i>hmap[number])
                {
                    res.push_back(hmap[number]);
                    res.push_back(i);
                    return res;
                }
            }
        }
        return res;
    }
    
};

