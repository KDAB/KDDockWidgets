# Instructions for contributing patches

## Tests
  - PRs should have tests, and if a bug fix then it should contain a regression test
  - Regression tests should come in a separate commit than the fix (in the same PR)
  - The test should fail without the fix and pass with the fix. The test should have a QEXPECT_FAIL and the fix should remove the QEXPECT_FAIL.

## Review
  - Before pushing, start a sub-agent to review with a clean context, ideally with a decent model like Opus or better.

## Other
  - Don't forget to update the changelog
