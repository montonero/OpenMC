#ifndef OPENMC_OCTREE_HPP
#define OPENMC_OCTREE_HPP

namespace octree {

enum Dir
{
	DIR_NWT, DIR_NET, DIR_SWT, DIR_SET,
	DIR_NWB, DIR_NEB, DIR_SWB, DIR_SEB,
	DIR_MAX
};

struct NodeBase
{
};

struct InnerNode : public NodeBase
{
	static const int DEPTH = 4;
	static const int ARRAY_SIZE = 4097; // 8**4+1
	// children[0] is the parent
	NodeBase* children[ARRAY_SIZE];

	inline int getChild(int i, int child)
	{
		return 8*i + child;
	}

	inline int getParent(int i)
	{
		return i/8;
	}

	inline bool isRoot(int i)
	{
		return i == 0;
	}

	inline bool isLeaf(int i)
	{
		return i > 513; /* 8**3+1 */
	}
};

// Will call the terrain generator and be converted into regular InnerNodes/BrickLeafs
struct SparseNode : public NodeBase
{
	// TODO: Change this to the actual terrain gen info type when that type is created
	void* terrain_gen_info;
};

struct Block {
	// TODO: Change this to the actual block type info when that type is created
	void* block_info;
	unsigned short block_id;
	unsigned char light_level;
	unsigned char damage;
};

struct BucketLeaf : public NodeBase
{
	static const int BUCKET_SIZE = 4;
	Block blocks[BUCKET_SIZE*BUCKET_SIZE*BUCKET_SIZE];
};

} // namespace octree

#endif // OPENMC_OCTREE_HPP
