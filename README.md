# K-D-Trees
INPUT FILE FORMAT:
<Point ID> <x-coordinate> <y-coordinate> <new line>

Techniques implemented:
(a) KD tree with bulk loading of data points read from a file
(b) Point Search operation on KD tree: This function searches for a single data point in the KD-tree
(c) Insert operation on KD tree: This function inserts a single data point into KD-tree and re-adjusts tree as needed

Specifications for the KD-tree construction
(1) Data structures for root, internal nodes and leaves should be clearly defined. Internal nodes should store the
following: (a) line used to split, (b) pointer to a left and right child, (c) if the current node is a left or a right child
of the parent, (d) pointer to the parent.
(2) Points on the line go to the left child. Left child of an internal node is left of the line or below the line.
(3) At root level you can define region as the smallest rectangle enclosing all the points in the dataset. This means that
regions at the internal node level are all subsets of this grand region defined at the root. You can store the region
(in form of xmin ymin xmax ymax) only at the root.
(4) Initially the tree must be bulk loaded using a recursive function which carries the whole set of points and divides
them accordingly. Point by point insertion (using the insert function) into KD tree is not allowed.
(5) At every level, you should choose the axis which has the largest spread and find the median data point by ordering
the data on the chosen axis.
(6) Region corresponding to an internal node should not be stored in the node, rather it should be generated on the fly
using the lines stored in the parents. You can generate the region on-the-fly while traversing the path from the root
to the current internal node.
(7) At any stage during insertion, splitting should not continue further if the current region has only alpha #data
points (parameter to be set in experiments) or less. In such a case, you need to create a leaf node. In this
implementation, leaf node would be an array of a user defined data type (called 2Dpoint). This array would be of
length alpha. In other words, each leaf node can store only alpha number of data points. Each data point stores the
following information: Point ID, x-coordinate and y-coordinate.
(8) Code must have a function named “PointInside” which takes a point and a region and returns a Boolean “Yes” if
the point is inside the region.
(9) Code should also have a function named “Visualize” which displays the KD tree by printing the internal node
information level-wise.

Point Search Operation in KD tree:
Implement a point search algorithm to run over your KD tree. This function takes a 2D point (x,y coordinate) as
input and checks if there exists a point in the KD tree with the same x and y coordinate. This function should use
the function described previously in item (8).


Insert Operation in KD tree:
Implement an insert operation for your KD tree. This function inserts a given 2D point (ID and x,y coordinate)
into the already constructed KD tree. Insert operation proceeds as follows: First, the algorithm “searches” for the
given 2D point in the tree to determine the appropriate leaf node LN where the given point can be inserted. Now,
if the leaf node has empty space (i.e., number of data points in the leaf is less than alpha ), then the operation goes
through straightforwardly. In case there is no space in LN , then it is divided into two new leaf nodes LNi and
LNj and the tree is updated accordingly. A new internal node IN is created at the place where LN was present
and the newly created LNi and LNj become its children.
