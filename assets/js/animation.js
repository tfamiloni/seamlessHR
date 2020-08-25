$(function () {
  let circles = [
    {
      target: ".onboarding-circle",
      image: ".onboarding-circle img",
      backgroundColor: "#D099D5",
      top: "-104.42%",
      left: "14.45%"
    },
    {
      target: ".time-circle",
      image: ".time-circle img",
      backgroundColor: "#9DDCA0",
      top: "-70.85%",
      left: "-67.86%"
    },
    {
      target: ".analytics-circle",
      image: ".analytics-circle img",
      backgroundColor: "#9DBCDC",
      top: "12.56%",
      left: "-104.97%"
    },
    {
      target: ".disciplinary-circle",
      image: ".disciplinary-circle img",
      backgroundColor: "#FBCB8C",
      top: "100.3%",
      left: "-70.85%"
    },
    {
      target: ".travel-circle",
      image: ".travel-circle img",
      backgroundColor: "#A7AFDD",
      top: "134.42%",
      left: "14.45%"
    },
    {
      target: ".exit-circle",
      image: ".exit-circle img",
      backgroundColor: "#F2EAA0",
      top: "100.3%",
      left: "99.75%"
    },
    {
      target: ".leave-circle",
      image: ".leave-circle img",
      backgroundColor: "#D0A48E",
      top: "12.56%",
      left: "136.31%"
    },
    {
      target: ".hris-circle",
      image: ".hris-circle img",
      backgroundColor: "#E69E9E",
      top: "-70.3%",
      left: "99.75%"
    }
  ];

  //ANIMATIONS START HERE
  const circleAnimation = () => {
    for (let [index, circle] of circles.entries()) {
      let tl = anime.timeline({
        easing: "easeOutExpo",
        targets: circle.target,
        duration: 2000
      });
      tl.add({
        top: circle.top,
        left: circle.left,
        backgroundColor: circle.backgroundColor,
        width: 125,
        height: 125,
        delay: 1000 + index * 200
      }).add(
        {
          targets: circle.image,
          scale: [0, 1],
          opacity: 1,
          duration: 1000,
          complete: function (el) {
            document.querySelector(circle.target).classList.add("pulse");
            if (index === circles.length - 1) {
              squareAnimation2();
            }
          }
        },
        "-=700"
      );
    }
  };

  const squareAnimation2 = () => {
    let tl = anime.timeline({
      easing: "easeOutExpo",
      duration: 1000
    });

    tl.add({
      targets: ".center-square",
      easing: "easeOutExpo",
      width: 181,
      height: 181
    }).add(
      {
        targets: ".center-square .images",
        opacity: [0, 1],
        duration: 2000,
        begin: imageHover(),
        complete: () => {
          document.querySelector(".circles").classList.add("rotate");
        }
      },
      "-=500"
    );
  };

  const imageHover = () => {
    let images = document.querySelectorAll(".center-square .images img");

    new hoverEffect({
      parent: document.querySelector(".center-square .images"),
      intensity: 0.3,
      image1: images[0].getAttribute("src"),
      image2: images[1].getAttribute("src"),
      displacementImage: "./assets/js/distortion.png"
    });
  };

  const squareAnimation = () => {
    let tl = anime.timeline({
      duration: 1000,
      easing: "easeOutExpo"
    });

    tl.add({
      targets: [
        ".blue-square",
        ".purple-square",
        ".green-square",
        ".center-square"
      ],
      opacity: [0, 1],
      delay: anime.stagger(100, { start: 1100 }),
      translateY: ["50px", "0"]
    })
      .add({
        targets: ".blue-square",
        left: ["0", "31.61%"],
        top: ["65.86%", "55.95%"],
        width: 40.46,
        height: 40.46,
        opacity: 0
      })
      .add(
        {
          targets: ".purple-square",
          left: "61.43%",
          top: "31.72%",
          width: 38.99,
          height: 38.99,
          opacity: 0
        },
        "-=1000"
      )
      .add(
        {
          targets: ".green-square",
          left: ["82.68%", "62.02%"],
          top: ["83.33%", "62.38%"],
          width: 22.81,
          height: 22.81,
          opacity: 0,
          complete: circleAnimation()
        },
        "-=1000"
      );
  };

  if (window.innerWidth >= 1200) squareAnimation();
});
