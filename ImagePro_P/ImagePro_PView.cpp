
// ImagePro_PView.cpp: CImageProPView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_P.h"
#endif

#include "ImagePro_PDoc.h"
#include "ImagePro_PView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProPView

IMPLEMENT_DYNCREATE(CImageProPView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProPView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Down_Sampling, &CImageProPView::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProPView::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProPView::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProPView::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProPView::OnSubConstant)
	ON_COMMAND(ID_MUL_COSTANT, &CImageProPView::OnMulCostant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProPView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProPView::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProPView::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProPView::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProPView::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProPView::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProPView::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProPView::OnStressTransform)
	ON_COMMAND(ID_HISTO_STRETCH, &CImageProPView::OnHistoStretch)
	ON_COMMAND(ID_END_IN_SEARCH, &CImageProPView::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CImageProPView::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CImageProPView::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CImageProPView::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CImageProPView::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CImageProPView::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProPView::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CImageProPView::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, &CImageProPView::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CImageProPView::OnLpfSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProPView::OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProPView::OnHomogenOperator)
	ON_COMMAND(ID_LAPLACIAN, &CImageProPView::OnLaplacian)
	ON_COMMAND(ID_NEAREST, &CImageProPView::OnNearest)
	ON_COMMAND(ID_BILINEAR, &CImageProPView::OnBilinear)
	ON_COMMAND(ID_MEDIAN_SUB, &CImageProPView::OnMedianSub)
	ON_COMMAND(ID_MEAN_SUB, &CImageProPView::OnMeanSub)
END_MESSAGE_MAP()

// CImageProPView 생성/소멸

CImageProPView::CImageProPView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProPView::~CImageProPView()
{
}

BOOL CImageProPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProPView 그리기

void CImageProPView::OnDraw(CDC* pDC)
{
	CImageProPDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	int i, j;
	unsigned char R, G, B;
	// 입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i * pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImageProPView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProPView 인쇄


void CImageProPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProPView 진단

#ifdef _DEBUG
void CImageProPView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProPView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProPDoc* CImageProPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProPDoc)));
	return (CImageProPDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProPView 메시지 처리기


void CImageProPView::OnDownSampling()
{
	// TODO: Add your command handler code here
   CImageProPDoc* pDoc = GetDocument(); // Doc 클래스 참조
   ASSERT_VALID(pDoc);

   pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

   Invalidate(TRUE); // 화면 갱신

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnUpSampling()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnQuantization()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

	Invalidate(TRUE); // 화면 갱신

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnSumConstant()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSumConstant();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnSubConstant()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();// 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnSubConstant();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnMulCostant()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnMulCostant();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnDivConstant()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument(); // 도큐먼트 클래스 참조
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnDivConstant();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnAndOperate()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnOrOperate()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnXorOperate()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnXorOperate();
	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnNegaTransform()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnGammaCorrection()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnBinarization()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnStressTransform()
{
	// TODO: Add your command handler code here
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHistoStretch()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnEndInSearch()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHistogram()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHistoEqual()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHistoSpec()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();

		Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnEmbossing()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnBlurr()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnGaussianFilter()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnSharpening()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHpfSharp()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnLpfSharp()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnDiffOperatorHor()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnHomogenOperator()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnLaplacian()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplacian();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnNearest()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNearest();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnBilinear()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnMedianSub()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianSub();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProPView::OnMeanSub()
{
	CImageProPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanSub();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
