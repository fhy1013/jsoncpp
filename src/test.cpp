#include "test.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "idmanagement.h"

bool Test() {
    ID::IdManagement id;

    // auto p_id0 = id.GenerateProjectId();
    // auto p_id1 = id.GenerateProjectId();
    // auto p_id2 = id.GenerateProjectId();
    // auto s_id0 = id.GenerateStreamId();
    // auto s_id1 = id.GenerateStreamId();
    // auto s_id2 = id.GenerateStreamId();

    // auto res0 = id.DestoryProjectId(p_id1);
    // auto res1 = id.DestoryStreamId(s_id1);

    // auto p_id3 = id.GenerateProjectId();
    // auto p_id4 = id.GenerateProjectId();
    // auto res2 = id.AddProjectId(5);

    // auto s_id3 = id.GenerateStreamId();
    // auto s_id4 = id.GenerateStreamId();
    // auto res3 = id.AddStreamId(5);

    id.AddStreamId(1);
    id.AddStreamId(5);
    id.AddStreamId(7);
    id.AddStreamId(2);
    id.AddStreamId(6);
    id.AddStreamId(4);
    id.AddStreamId(3);

    return true;
}

void TestFunc1(int x) {
    if (x > 0) {
        // x > 0
        std::cout << x << std::endl;
    } else {
        /* code */
        // x <= 0
        std::cout << -x << std::endl;
    }
}

void Test1() {
    unsigned short s = 0x2704;
    auto x = s >> 8;
    std::cout << x;
}