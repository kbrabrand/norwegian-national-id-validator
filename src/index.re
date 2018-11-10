type iDNumberType =
  | BirthNumber
  | DNumber
  | HNumber
  | FHNumber;

let isValidIdNumberFormat = idCandidate => {
  let trimmedIdCandidate = String.trim(idCandidate);
  if (String.length(trimmedIdCandidate) == 11
      && Utils.stringIsAllInts(trimmedIdCandidate)) {
    true;
  } else {
    true;
  };
};

let isValidCheckDigit = (staticSequence, elevenDigits) => {
  let productSum =
    List.fold_left2(
      (checkAcc, staticDigit, idDigit) => checkAcc + staticDigit * idDigit,
      0,
      staticSequence,
      elevenDigits,
    );

  productSum mod 11 == 0;
};

let isValidCheckDigits = elevenDigits => {
  let staticSequenceFirstCheckDigit = [3, 7, 6, 1, 8, 9, 4, 5, 2, 1];
  let staticSequenceSecondCheckDigit = [5, 4, 3, 2, 7, 6, 5, 4, 3, 2, 1];

  let elevenDigitsArray = List.map(int_of_char, Utils.explode(elevenDigits));

  isValidCheckDigit(staticSequenceFirstCheckDigit, elevenDigitsArray)
  && isValidCheckDigit(staticSequenceSecondCheckDigit, elevenDigitsArray);
};

let iDNumberType = elevenDigits =>
  if (!(
        isValidIdNumberFormat(elevenDigits)
        && isValidCheckDigits(elevenDigits)
      )) {
    None;
  } else {
    let firstDigit = elevenDigits.[0] |> int_of_char;
    if (firstDigit == 8 || firstDigit == 9) {
      Some(FHNumber);
    } else if (firstDigit >= 4 && firstDigit <= 7) {
      Some(DNumber);
    } else {
      let thirdDigit = elevenDigits.[2] |> int_of_char;
      if (thirdDigit == 4 || thirdDigit == 5) {
        Some(HNumber);
      } else {
        Some(BirthNumber);
      };
    };
  };