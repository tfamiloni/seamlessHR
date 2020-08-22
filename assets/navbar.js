document.addEventListener("DOMContentLoaded", () => {
  let links = document.querySelectorAll(".nav-link, .platform-item");

  let currentPage = window.location.pathname.split("/").pop();

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
  setActive();

  let checkedProduct = null;
  const comparison = () => {
    for (let i = 0; i < productSelectors.length; i++) {
      if (productSelectors[i].checked) {
        checkedProduct = productSelectors[i].getAttribute("id");
        break;
      }
    }

    for (rival of rivalInfo) {
      rival.getAttribute("data-competitor") === checkedProduct
        ? rival.classList.add("d-flex")
        : rival.classList.remove("d-flex");
    }
  };

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

  const companySubMenus = [
    "about.html",
    "careers.html",
    "customer-stories.html",
    "why-seamless.html",
    "press.html",
    "partners.html"
  ];

  const resourcesSubMenus = [
    "FAQ.html",
    "insights.html",
    "guides-tutorials.html",
    "ebooks.html",
    "blog.html"
  ];

  if (!showTopFooter.includes(currentPage)) {
    document.querySelector(".footer__top").classList.add("d-none");
  }

  if (platformSubMenus.includes(currentPage)) {
    document
      .getElementById("platformDropdownMenuLabel")
      .classList.add("active");
  }

  if (companySubMenus.includes(currentPage)) {
    document.getElementById("companyDropdownLink").classList.add("active");
  }

  if (resourcesSubMenus.includes(currentPage)) {
    document
      .getElementById("resourcesDropdownMenuLink")
      .classList.add("active");
  }
});
