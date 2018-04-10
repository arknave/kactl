/**
 * Author: Stjepan Glavina
 * Date: 2016-08-18
 * License: Unlicense
 * Source: stjepang/snippets
 * Description: Division
 * Time: $O(1)$
 */
#pragma once

ll div_floor(ll a, ll b) {
  if (b < 0) a = -a, b = -b;
  return a/b - (a%b < 0);
}

ll div_ceil(ll a, ll b) {
  if (b < 0) a = -a, b = -b;
  return a/b + (a%b > 0);
}
