document.addEventListener("DOMContentLoaded", () => {
  let links = document.querySelectorAll(".nav-link, .platform-item");

  let currentPage = window.location.pathname.split("/")[1];

  let rivalInfo = document.querySelectorAll(".rival-info");
  let productSelectors = document.querySelectorAll(
    ".product-comparison__radio"
  );

  const setActive = () => {
    for (let link of links) {
      if (link.getAttribute("href") === currentPage) {
        link.classList.add("active");
      }

      if (
        currentPage === "index.html" &&
        link.getAttribute("href") === "index.html"
      ) {
        link.classList.add("active");
      }
    }
  };

  const comparison = () => {
    for (let i = 0; i < productSelectors.length; i++) {
      if (productSelectors[i].checked) {
        for (rival of rivalInfo) {
          if (
            productSelectors[i].getAttribute("id") ===
            rival.getAttribute("data-competitor")
          ) {
            rival.classList.add("d-flex");
          } else {
            rival.classList.remove("d-flex");
          }
        }
      }
    }
  };

  const randomiseFeature = () => {
    let featureInputs = document.querySelectorAll(
      '.carousel input[type="radio"]'
    );
    let randomNumber = Math.round(Math.random() * featureInputs.length);
    featureInputs[randomNumber].checked = true;
  };

  setActive();
  comparison();
  document
    .querySelector(".product-comparison__selector-grid")
    .addEventListener("click", comparison);

  if (currentPage === "core-hr.html") {
    randomiseFeature();
  }

  if (currentPage === "pricing.html") {
    comparison();
    document
      .querySelector(".product-comparison__selector-grid")
      .addEventListener("click", comparison);
  }

  const showTopFooter = [
    "index.html",
    "pricing.html",
    "performance-management.html",
    "recruitment-management.html"
  ];

  const platformSubMenus = [
    "core-hr.html",
    "performance-management.html",
    "recruitment-management.html",
    "payroll-management.html"
  ];

  if (!showTopFooter.includes(currentPage)) {
    document.querySelector(".footer__top").classList.add("d-none");
  }

  if (platformSubMenus.includes(currentPage)) {
    document
      .getElementById("platformDropdownMenuLabel")
      .classList.add("active");
  }
});
