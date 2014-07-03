#include <bandit/bandit.h>

#include "TestConstants.hpp"

using namespace bandit;

go_bandit([]()
{
    describe("an example test", []()
    {
        it("makes a verifiable assertion", []()
        {
            AssertThat(2 + 2, Is().EqualTo(4));
        });
    });
});
