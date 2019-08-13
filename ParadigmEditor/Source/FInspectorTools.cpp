#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
#define DOUBLE_MIN std::numeric_limits<double>::min()
#define DOUBLE_MAX std::numeric_limits<double>::max()

	void FParadigmEditor::ShowClass(QWidget* _parent)
	{
		m_ClassContainer = new QWidget(_parent);
		m_ClassContainer->setGeometry(QRect(QPoint(0, 10), QSize(1500, 100)));
		m_ClassContainer->setHidden(true);
		m_ClassEdit = new QLineEdit(m_ClassContainer);
		m_ClassEdit->setStyleSheet("font-weight: bold; background-color: #131414;");
		m_ClassEdit->setAlignment(Qt::AlignCenter);
		QCheckBox* isShown = new QCheckBox(m_ClassContainer);
		isShown->setChecked(true);
		isShown->setStyleSheet("background-color: #131414;");

		m_ClassEdit->move(50, 0);
		isShown->move(10, 0);

		CreateSpacing(m_ClassContainer, "background-color: #E2E2E2;", 30);

		connect(m_ClassEdit, &QLineEdit::textChanged, this, [=]()
		{
			m_HierarchyTree->currentItem()->setText(0, m_ClassEdit->text());
		});
	}

	void FParadigmEditor::CreateBool(QWidget* _parent)
	{
		m_BoolContainer = new QWidget(_parent);
		m_BoolContainer->setGeometry(QRect(QPoint(0, 55), QSize(1500, 100)));
		m_BoolContainer->setHidden(true);
		m_VisibleLabel = new QLabel("Visible", m_BoolContainer);
		m_VisibleLabel->setHidden(true);
		QCheckBox* visibleCheckBox = new QCheckBox(m_BoolContainer);
		visibleCheckBox->setStyleSheet("background-color: #131414;");

		//m_BoolContainer->move(0, 55);
		m_VisibleLabel->move(10, 0);
		visibleCheckBox->move(60, 0);

		CreateSpacing(m_BoolContainer, "background-color: #FFB712;", 25);
	}

	void FParadigmEditor::CreateEnum(QWidget* _parent)
	{
		m_EnumContainer = new QWidget(_parent);
		m_EnumContainer->setGeometry(QRect(QPoint(0, 175), QSize(1500, 100)));

		m_EnumContainer->setHidden(true);
		m_EnumLabel = new QLabel("Animation", m_EnumContainer);
		m_EnumLabel->setHidden(true);;
		QComboBox* animation = new QComboBox(m_EnumContainer);
		animation->addItem("Walk");
		animation->addItem("Run");
		animation->addItem("Attack");
		animation->addItem("Win");
		animation->addItem("Death");
		//QVariant val = animation->itemData(animation->currentIndex());

		m_EnumContainer->move(0, 175);
		m_EnumLabel->move(10, 3);
		animation->move(75, 0);

		CreateSpacing(m_EnumContainer, "background-color: #FFB712;", 30);
	}

	void FParadigmEditor::CreateTransform(QWidget* _parent)
	{
		m_TransformContainer = new QWidget(_parent);
		m_TransformContainer->setGeometry(QRect(QPoint(0, 90), QSize(1500, 250)));
		m_TransformContainer->setHidden(true);
		m_PosLabel = new QLabel("Position", m_TransformContainer);
		m_PosLabel->setGeometry(QRect(QPoint(10, 3), QSize(800, 10)));
		m_PosLabel->setHidden(true);

		/* Position */
		QLabel* xPosLabel = new QLabel("X: ", m_TransformContainer);
		xPosLabel->setGeometry(QRect(QPoint(65, 3), QSize(400, 10)));
		QDoubleSpinBox* xPosVal = new QDoubleSpinBox(m_TransformContainer);
		xPosVal->setGeometry(QRect(QPoint(80, -1), QSize(55, 20)));
		xPosLabel->setStyleSheet("color: #FFB712;");
		xPosVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		xPosVal->setMinimum(DOUBLE_MIN);
		xPosVal->setMaximum(DOUBLE_MAX);

		QLabel* yPosLabel = new QLabel("Y: ", m_TransformContainer);
		yPosLabel->setGeometry(QRect(QPoint(140, 3), QSize(400, 10)));
		QDoubleSpinBox* yPosVal = new QDoubleSpinBox(m_TransformContainer);
		yPosVal->setGeometry(QRect(QPoint(155, -1), QSize(55, 20)));
		yPosLabel->setStyleSheet("color: #FFB712;");
		yPosVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		yPosVal->setMinimum(DOUBLE_MIN);
		yPosVal->setMaximum(DOUBLE_MAX);

		QLabel* zPosLabel = new QLabel("Z: ", m_TransformContainer);
		zPosLabel->setGeometry(QRect(QPoint(215, 3), QSize(400, 10)));
		QDoubleSpinBox* zPosVal = new QDoubleSpinBox(m_TransformContainer);
		zPosVal->setGeometry(QRect(QPoint(230, -1), QSize(55, 20)));
		zPosLabel->setStyleSheet("color: #FFB712;");
		zPosVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		zPosVal->setMinimum(DOUBLE_MIN);
		zPosVal->setMaximum(DOUBLE_MAX);

		/* Rotation */
		m_RotLabel = new QLabel("Rotation", m_TransformContainer);
		m_RotLabel->setGeometry(QRect(QPoint(10, 30), QSize(800, 10)));
		m_RotLabel->setHidden(true);

		QLabel* xRotLabel = new QLabel("X: ", m_TransformContainer);
		xRotLabel->setGeometry(QRect(QPoint(65, 30), QSize(400, 10)));
		QDoubleSpinBox* xRotVal = new QDoubleSpinBox(m_TransformContainer);
		xRotVal->setGeometry(QRect(QPoint(80, 25), QSize(55, 20)));
		xRotLabel->setStyleSheet("color: #FFB712;");
		xRotVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		xRotVal->setMinimum(DOUBLE_MIN);
		xRotVal->setMaximum(DOUBLE_MAX);

		QLabel* yRotLabel = new QLabel("Y: ", m_TransformContainer);
		yRotLabel->setGeometry(QRect(QPoint(140, 30), QSize(400, 10)));
		QDoubleSpinBox* yRotVal = new QDoubleSpinBox(m_TransformContainer);
		yRotVal->setGeometry(QRect(QPoint(155, 25), QSize(55, 20)));
		yRotLabel->setStyleSheet("color: #FFB712;");
		yRotVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		yRotVal->setMinimum(DOUBLE_MIN);
		yRotVal->setMaximum(DOUBLE_MAX);

		QLabel* zRotLabel = new QLabel("Z: ", m_TransformContainer);
		zRotLabel->setGeometry(QRect(QPoint(215, 30), QSize(400, 10)));
		QDoubleSpinBox* zRotVal = new QDoubleSpinBox(m_TransformContainer);
		zRotVal->setGeometry(QRect(QPoint(230, 25), QSize(55, 20)));
		zRotLabel->setStyleSheet("color: #FFB712;");
		zRotVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		zRotVal->setMinimum(DOUBLE_MIN);
		zRotVal->setMaximum(DOUBLE_MAX);


		/* Scale */
		m_ScaleLabel = new QLabel("Scale", m_TransformContainer);
		m_ScaleLabel->setGeometry(QRect(QPoint(10, 57), QSize(800, 10)));
		m_ScaleLabel->setHidden(true);

		QLabel* xScaleLabel = new QLabel("X: ", m_TransformContainer);
		xScaleLabel->setGeometry(QRect(QPoint(65, 57), QSize(400, 10)));
		QDoubleSpinBox* xScaleVal = new QDoubleSpinBox(m_TransformContainer);
		xScaleVal->setGeometry(QRect(QPoint(80, 51), QSize(55, 20)));
		xScaleLabel->setStyleSheet("color: #FFB712;");
		xScaleVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		xScaleVal->setMinimum(DOUBLE_MIN);
		xScaleVal->setMaximum(DOUBLE_MAX);

		QLabel* yScaleLabel = new QLabel("Y: ", m_TransformContainer);
		yScaleLabel->setGeometry(QRect(QPoint(140, 57), QSize(400, 10)));
		QDoubleSpinBox* yScaleVal = new QDoubleSpinBox(m_TransformContainer);
		yScaleVal->setGeometry(QRect(QPoint(155, 51), QSize(55, 20)));
		yScaleLabel->setStyleSheet("color: #FFB712;");
		yScaleVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		yScaleVal->setMinimum(DOUBLE_MIN);
		yScaleVal->setMaximum(DOUBLE_MAX);

		QLabel* zScaleLabel = new QLabel("Z: ", m_TransformContainer);
		zScaleLabel->setGeometry(QRect(QPoint(215, 57), QSize(400, 10)));
		QDoubleSpinBox* zScaleVal = new QDoubleSpinBox(m_TransformContainer);
		zScaleVal->setGeometry(QRect(QPoint(230, 51), QSize(55, 20)));
		zScaleLabel->setStyleSheet("color: #FFB712;");
		zScaleVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		zScaleVal->setMinimum(DOUBLE_MIN);
		zScaleVal->setMaximum(DOUBLE_MAX);

		CreateSpacing(m_TransformContainer, "background-color: #FFB712;", 75);
	}

	void FParadigmEditor::CreateSpacing(QWidget* _parent, const QString& _color, int _posY)
	{
		QFrame* spacing = new QFrame(_parent);
		spacing->setFrameShadow(QFrame::Sunken);
		spacing->setGeometry(QRect(QPoint(0, _posY), QSize(3000, 2)));
		spacing->setStyleSheet(_color);
	}
}